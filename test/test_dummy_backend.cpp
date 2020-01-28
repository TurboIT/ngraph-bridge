/*******************************************************************************
 * Copyright 2017-2020 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *******************************************************************************/

#include "gtest/gtest.h"

#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/public/session.h"

#include "logging/tf_graph_writer.h"
#include "test/dummy_backend.h"
#include "test/test_utilities.h"

using namespace std;
namespace ng = ngraph;

namespace tensorflow {

namespace ngraph_bridge {

namespace testing {

// Test is_supported API
TEST(DummyBackend, IsSupported) {
  ngraph::runtime::dummy::DummyBackend db;
  auto add = std::make_shared<ngraph::op::Add>();
  ASSERT_EQ(db.is_supported(*add), false);
  // TODO add a test where we compile and get an executable


  ngraph::runtime::dummy::DummyBackend2 db2;
  ASSERT_EQ(db2.is_supported(*add), true);


  ngraph::runtime::dummy::DummyBackend3 db3;
  ASSERT_EQ(db3.is_supported(*add), false);
  db3.set_supported_behaviour({std::make_shared<ngraph::op::Add>()});
  ASSERT_EQ(db3.is_supported(*add), true);
}

}  // namespace testing
}  // namespace ngraph_bridge
}  // namespace tensorflow
