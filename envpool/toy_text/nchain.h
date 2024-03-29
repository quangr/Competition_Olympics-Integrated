/*
 * Copyright 2021 Garena Online Private Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
// https://github.com/openai/gym/blob/v0.20.0/gym/envs/toy_text/nchain.py

#ifndef ENVPOOL_TOY_TEXT_NCHAIN_H_
#define ENVPOOL_TOY_TEXT_NCHAIN_H_

#include <algorithm>
#include <cmath>
#include <random>
#include <string>
#include <vector>

#include "envpool/core/async_envpool.h"
#include "envpool/core/env.h"

namespace toy_text {

class NChainEnvFns {
 public:
  static decltype(auto) DefaultConfig() {
    return MakeDict("max_episode_steps"_.bind(1000));
  }
  template <typename Config>
  static decltype(auto) StateSpec(const Config& conf) {
    return MakeDict("obs"_.bind(Spec<int>({-1}, {0, 4})));
  }
  template <typename Config>
  static decltype(auto) ActionSpec(const Config& conf) {
    return MakeDict("action"_.bind(Spec<int>({-1}, {0, 1})));
  }
};

typedef class EnvSpec<NChainEnvFns> NChainEnvSpec;

class NChainEnv : public Env<NChainEnvSpec> {
 protected:
  int s_, max_episode_steps_, elapsed_step_;
  std::uniform_real_distribution<> dist_;
  bool done_;

 public:
  NChainEnv(const Spec& spec, int env_id)
      : Env<NChainEnvSpec>(spec, env_id),
        max_episode_steps_(spec.config["max_episode_steps"_]),
        dist_(0, 1),
        done_(true) {}

  bool IsDone() override { return done_; }

  void Reset() override {
    s_ = 0;
    done_ = false;
    elapsed_step_ = 0;
    State state = Allocate();
    WriteObs(state, 0.0f);
  }

  void Step(const Action& action) override {
    done_ = (++elapsed_step_ >= max_episode_steps_);
    int act = action["action"_];
    if (dist_(gen_) < 0.2) {
      act = 1 - act;
    }
    float reward = 0.0f;
    if (act) {
      reward = 2.0f;
      s_ = 0;
    } else if (s_ < 4) {
      ++s_;
    } else {
      reward = 10.0f;
    }
    State state = Allocate();
    WriteObs(state, reward);
  }

 private:
  void WriteObs(State& state, float reward) {  // NOLINT
    state["obs"_] = s_;
    state["reward"_] = reward;
  }
};

typedef AsyncEnvPool<NChainEnv> NChainEnvPool;

}  // namespace toy_text

#endif  // ENVPOOL_TOY_TEXT_NCHAIN_H_
