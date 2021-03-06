// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include <header.hpp>

TEST(konstrukt, first) {
  Json a(
      "{\"lastname\":\"Ivanov\",\"firstname\":\"Ivan\",\"age\":25,\"islegal\":"
      "false,\"marks\":[4,5,5,5,2,3],\"address\":{\"city\":\"Moscow\","
      "\"street\":\"Vozdvijenka\"}}");
  EXPECT_EQ(std::any_cast<std::string>(a["lastname"]), "Ivanov");
  EXPECT_EQ(std::any_cast<std::string>(a["firstname"]), "Ivan");
  EXPECT_EQ(std::any_cast<bool>(a["islegal"]), false);
  EXPECT_EQ(std::any_cast<int>(std::any_cast<Json>(a["marks"])[0]), 4);
  EXPECT_EQ(std::any_cast<int>(std::any_cast<Json>(a["marks"])[1]), 5);
  EXPECT_EQ(std::any_cast<int>(std::any_cast<Json>(a["marks"])[2]), 5);
  EXPECT_EQ(std::any_cast<int>(std::any_cast<Json>(a["marks"])[3]), 5);
  EXPECT_EQ(std::any_cast<int>(std::any_cast<Json>(a["marks"])[4]), 2);
  EXPECT_EQ(std::any_cast<int>(std::any_cast<Json>(a["marks"])[5]), 3);
  EXPECT_EQ(std::any_cast<std::string>(std::any_cast<std::string>(
                std::any_cast<Json>(a["address"])["city"])),
            "Moscow");
}

TEST(parse, first) {
  Json a = Json::parse(
      "{\"lastname\":\"Ivanov\",\"firstname\":\"Ivan\",\"age\":25,\"islegal\":"
      "false,\"marks\":[4,5,5,5,2,3],\"address\":{\"city\":\"Moscow\","
      "\"street\":\"Vozdvijenka\"}}");
  EXPECT_EQ(std::any_cast<std::string>(a["lastname"]), "Ivanov");
  EXPECT_EQ(std::any_cast<std::string>(a["firstname"]), "Ivan");
  EXPECT_EQ(std::any_cast<bool>(a["islegal"]), false);
  EXPECT_EQ(std::any_cast<int>(std::any_cast<Json>(a["marks"])[0]), 4);
  EXPECT_EQ(std::any_cast<int>(std::any_cast<Json>(a["marks"])[1]), 5);
  EXPECT_EQ(std::any_cast<int>(std::any_cast<Json>(a["marks"])[2]), 5);
  EXPECT_EQ(std::any_cast<int>(std::any_cast<Json>(a["marks"])[3]), 5);
  EXPECT_EQ(std::any_cast<int>(std::any_cast<Json>(a["marks"])[4]), 2);
  EXPECT_EQ(std::any_cast<int>(std::any_cast<Json>(a["marks"])[5]), 3);
  EXPECT_EQ(std::any_cast<std::string>(std::any_cast<std::string>(
                std::any_cast<Json>(a["address"])["city"])),
            "Moscow");
}

TEST(file, first) {
  Json a = Json::parseFile("../file.json");
  EXPECT_EQ(std::any_cast<std::string>(a["lastname"]), "Ivanov");
  EXPECT_EQ(std::any_cast<std::string>(a["firstname"]), "Ivan");
  EXPECT_EQ(std::any_cast<bool>(a["islegal"]), false);
  EXPECT_EQ(std::any_cast<int>(std::any_cast<Json>(a["marks"])[0]), 4);
  EXPECT_EQ(std::any_cast<int>(std::any_cast<Json>(a["marks"])[1]), 5);
  EXPECT_EQ(std::any_cast<int>(std::any_cast<Json>(a["marks"])[2]), 5);
  EXPECT_EQ(std::any_cast<int>(std::any_cast<Json>(a["marks"])[3]), 5);
  EXPECT_EQ(std::any_cast<int>(std::any_cast<Json>(a["marks"])[4]), 2);
  EXPECT_EQ(std::any_cast<int>(std::any_cast<Json>(a["marks"])[5]), 3);
  EXPECT_EQ(std::any_cast<std::string>(std::any_cast<std::string>(
                std::any_cast<Json>(a["address"])["city"])),
            "Moscow");
}
