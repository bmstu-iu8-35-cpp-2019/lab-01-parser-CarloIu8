// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include <header.hpp>

Json a(
    "{\"response\":[{\"id\":210700286,\"first_name\":\"Lindsey\",\"last_name\":"
    "\"Stirling\"}]}");
TEST(circuits, first) {
  Json a(
      "{\"lastname\":\"Ivanov\",\"firstname\":\"Ivan\",\"age\":25,\"islegal\":"
      "false,\"marks\":[4,5,5,5,2,3],\"address\":{\"city\":\"Moscow\","
      "\"street\":\"Vozdvijenka\"}}")

      EXPECT_EQ(any_cast<string>(a["lastname"]), "Ivanov");
  EXPECT_EQ(any_cast<string>(a["firstname"]), "Ivan");
  EXPECT_EQ(any_cast<string>(a["islegal"]), false);
  EXPECT_EQ(any_cast<int>(std::any_cast<Json>(a["marks"])[0]), 4);
  EXPECT_EQ(any_cast<int>(std::any_cast<Json>(a["marks"])[1]), 5);
  EXPECT_EQ(any_cast<int>(std::any_cast<Json>(a["marks"])[2]), 5);
  EXPECT_EQ(any_cast<int>(std::any_cast<Json>(a["marks"])[3]), 5);
  EXPECT_EQ(any_cast<int>(std::any_cast<Json>(a["marks"])[4]), 2);
  EXPECT_EQ(any_cast<int>(std::any_cast<Json>(a["marks"])[5]), 3);
  EXPECT_EQ(
      any_cast<string>(any_cast<string>(any_cast<Json>(a["address"])["city"])),
      "Moscow");
}
