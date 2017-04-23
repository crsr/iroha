/*
Copyright Soramitsu Co., Ltd. 2016 All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#ifndef IROHA_VALIDATOR_H
#define IROHA_VALIDATOR_H

#include <generated/main_generated.h>

// This is stateless validator.
namespace validator{
    using iroha::Transaction;
    bool require_property_validator(const iroha::Transaction& tx);
    bool account_exist_validator(const iroha::Transaction& tx);
};
#endif //IROHA_VALIDATOR_H
