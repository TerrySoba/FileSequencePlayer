#include "catch.hpp"

#include "test_data.h"
#include "file_sequence_finder_boost.h"

TEST_CASE("FileSequenceFinderBoostTest") {

    QString testSequenceDir = TEST_DATA_DIR + "/testsequence/";

    FileSequenceFinderBoost finder;

    SECTION("Numbered sequences work")
    {
        auto result = finder.getFileSequence(testSequenceDir + "0106.jpg");

        REQUIRE(result.size() == 3);
        REQUIRE(result.at(0).endsWith("0106.jpg"));
        REQUIRE(result.at(1).endsWith("0107.jpg"));
        REQUIRE(result.at(2).endsWith("0108.jpg"));
    }

    SECTION("Un-numbered images work")
    {
        auto result = finder.getFileSequence(testSequenceDir + "unnumbered.jpg");
        REQUIRE(result.size() == 1);
        REQUIRE(result.at(0).endsWith("unnumbered.jpg"));
    }

    SECTION("Invalid paths throw exception")
    {
        REQUIRE_THROWS(finder.getFileSequence(testSequenceDir + "unknownfile"));
        REQUIRE_THROWS(finder.getFileSequence(""));
    }
}
