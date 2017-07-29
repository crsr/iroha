/**
 * Copyright Soramitsu Co., Ltd. 2017 All Rights Reserved.
 * http://soramitsu.co.jp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "genesis_block_processor_impl.hpp"
#include "logger/logger.hpp"

logger::Logger Log("GenesisBlockProcessor");

namespace iroha {
  bool GenesisBlockProcessorImpl::genesis_block_handle(
      const iroha::model::Block &block) {
    auto wsv = temporary_factory_.createTemporaryWsv();

    for (const auto &tx : block.transactions) {
      auto result =
          wsv->apply(tx, [](const auto &tx, auto &executor, auto &query) {
            for (const auto &command : tx.commands) {
              auto valid = command->execute(query, executor);
              if (!valid) return false;
            }
            return true;
          });
      if (!result) {
        return false;
      }
    }

    auto ms = mutable_factory_.createMutableStorage();

    auto result = ms->apply(block, [](const auto &blk, auto &executor,
                                      auto &query, const auto &top_hash) {
      for (const auto &tx : blk.transactions) {
        for (const auto &command : tx.commands) {
          auto valid = command->execute(query, executor);
          if (!valid) return false;
        }
      }
      return true;
    });

    if (result) {
      mutable_factory_.commit(std::move(ms));
    }

    return result;
  }
}  // namespace iroha
