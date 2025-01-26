#include <gtest/gtest.h>
#include "../lib/sheduler.h"
#include "cmath"

TEST(three_args, Simple
) {
  float a = 1;
  float b = -2;
  float c = 0;
  TTaskScheduler scheduler;

  auto id1 = scheduler.add([](float a, float c) { return -4 * a * c; }, a, c);

  auto id2 = scheduler.add([](float b, float v) { return b * b + v; }, b, scheduler.getFutureResult<float>(id1));

  auto
      id3 = scheduler.add([](float b, float d) { return -b + std::sqrt(d); }, b, scheduler.getFutureResult<float>(id2));

  auto
      id4 = scheduler.add([](float b, float d) { return -b - std::sqrt(d); }, b, scheduler.getFutureResult<float>(id2));

  auto id5 = scheduler.add([](float a, float v) { return v / (2 * a); }, a, scheduler.getFutureResult<float>(id3));

  auto id6 = scheduler.add([](float a, float v) { return v / (2 * a); }, a, scheduler.getFutureResult<float>(id4));

  scheduler.executeAll();

  ASSERT_EQ(scheduler.getResult<float>(id5), 2);
  ASSERT_EQ(scheduler.getResult<float>(id6), 0);
}

TEST(three_args, Quadro
) {
  float a = 1;
  float b = -2;
  float c = 1;
  TTaskScheduler scheduler;

  auto id1 = scheduler.add([](float a, float c) { return -4 * a * c; }, a, c);

  auto id2 = scheduler.add([](float b, float v) { return b * b + v; }, b, scheduler.getFutureResult<float>(id1));

  auto
      id3 = scheduler.add([](float b, float d) { return -b + std::sqrt(d); }, b, scheduler.getFutureResult<float>(id2));

  auto
      id4 = scheduler.add([](float b, float d) { return -b - std::sqrt(d); }, b, scheduler.getFutureResult<float>(id2));

  auto id5 = scheduler.add([](float a, float v) { return v / (2 * a); }, a, scheduler.getFutureResult<float>(id3));

  auto id6 = scheduler.add([](float a, float v) { return v / (2 * a); }, a, scheduler.getFutureResult<float>(id4));

  scheduler.executeAll();

  ASSERT_EQ(scheduler.getResult<float>(id5), 1);
  ASSERT_EQ(scheduler.getResult<float>(id6), 1);
}

TEST(three_args, Zero
) {
  float a = 1;
  float b = 0;
  float c = 0;
  TTaskScheduler scheduler;

  auto id1 = scheduler.add([](float a, float c) { return -4 * a * c; }, a, c);

  auto id2 = scheduler.add([](float b, float v) { return b * b + v; }, b, scheduler.getFutureResult<float>(id1));

  auto
      id3 = scheduler.add([](float b, float d) { return -b + std::sqrt(d); }, b, scheduler.getFutureResult<float>(id2));

  auto
      id4 = scheduler.add([](float b, float d) { return -b - std::sqrt(d); }, b, scheduler.getFutureResult<float>(id2));

  auto id5 = scheduler.add([](float a, float v) { return v / (2 * a); }, a, scheduler.getFutureResult<float>(id3));

  auto id6 = scheduler.add([](float a, float v) { return v / (2 * a); }, a, scheduler.getFutureResult<float>(id4));

  scheduler.executeAll();

  ASSERT_EQ(scheduler.getResult<float>(id5), 0);
  ASSERT_EQ(scheduler.getResult<float>(id6), 0);
}

TEST(two_args, Zero
) {
  float a = 1;
  float b = -4;

  TTaskScheduler scheduler;

  auto id1 = scheduler.add([](float a) { return -4 * a; }, a);

  auto id2 = scheduler.add([](float b, float v) { return b * b - v; }, b, scheduler.getFutureResult<float>(id1));

  scheduler.executeAll();

  ASSERT_EQ(scheduler.getResult<float>(id1), -4);
  ASSERT_EQ(scheduler.getResult<float>(id2), 20);
}

TEST(one_args, Zero
) {
  float a = 1;

  TTaskScheduler scheduler;

  auto id1 = scheduler.add([](float a) { return -4 * a; }, a);

  auto id2 = scheduler.add([](float b) { return b * b; }, scheduler.getFutureResult<float>(id1));

  scheduler.executeAll();

  ASSERT_EQ(scheduler.getResult<float>(id1), -4);
  ASSERT_EQ(scheduler.getResult<float>(id2), 16);
}
