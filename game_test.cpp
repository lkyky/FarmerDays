#define CATCH_CONFIG_MAIN

#include "catch_amalgamated.hpp"
#include "utilities.h"
#include <vector>
#include "player.h"
#include "crop.h"
#include "farm.h"
#include "highscore.h"

static crop_data create_crop(const string &name, int growth_time, int price)
{
    crop_data c;
    c.crop_name = name;
    c.growth_time = growth_time;
    c.price = price;
    return c;
}

TEST_CASE("Score - calculate_score uses coins + level*200 + crops*5")
{
    player_data p;
    p.player_name = "A";
    p.level = 3;
    p.coin = 120;
    p.hp = 100;
    p.total_planted_crops = 10;
    p.inventory_head = nullptr;

    // expected = 120 + (3*200) + (10*5) = 770
    REQUIRE(calculate_score(p) == 770);
}

TEST_CASE("Coins - can_afford returns true only when player has enough coins")
{
    player_data p;
    p.coin = 100;

    REQUIRE(can_afford(p, 0) == true);
    REQUIRE(can_afford(p, 50) == true);
    REQUIRE(can_afford(p, 100) == true);
    REQUIRE(can_afford(p, 101) == false);
}

TEST_CASE("Coins - spend_coins reduces coins and clamps at 0 (no negative)")
{
    player_data p;
    p.coin = 120;

    spend_coins(p, 50);
    REQUIRE(p.coin == 70);

    spend_coins(p, 1000);   // overspend should clamp to 0 too
    REQUIRE(p.coin == 0);
}

TEST_CASE("Farm Timer - update_farm_timer decreases time and clamps at 0")
{
    farm_data f;
    f.max_capacity = 100;
    f.used_capacity = 0;

    planted_crop a;
    a.crop = create_crop("Mint", 10, 6);
    a.quantity = 5;
    a.time_remaining = 10;

    planted_crop b;
    b.crop = create_crop("Wheat", 60, 10);
    b.quantity = 2;
    b.time_remaining = 3;

    f.planted.push_back(a);
    f.planted.push_back(b);

    SECTION("Decreases time_remaining by seconds")
    {
        update_farm_timer(f, 4);
        REQUIRE(f.planted[0].time_remaining == 6);
        REQUIRE(f.planted[1].time_remaining == 0);  // clamp to 0
    }

    SECTION("Seconds == 0 makes no change")
    {
        update_farm_timer(f, 0);
        REQUIRE(f.planted[0].time_remaining == 10);
        REQUIRE(f.planted[1].time_remaining == 3);
    }

    SECTION("Negative seconds should do nothing")
    {
        update_farm_timer(f, -5);
        REQUIRE(f.planted[0].time_remaining == 10);
        REQUIRE(f.planted[1].time_remaining == 3);
    }
}

TEST_CASE("Inventory - add_to_inventory adds new node and increases quantity on same crop")
{
    player_data p;
    p.player_name = "Test";
    p.inventory_head = nullptr;
    p.level = 1;
    p.coin = 0;
    p.hp = 100;
    p.total_planted_crops = 0;

    crop_data mint = create_crop("Mint", 10, 6);
    crop_data wheat = create_crop("Wheat", 60, 10);

    add_to_inventory(p, mint, 5);
    REQUIRE(p.inventory_head != nullptr);
    REQUIRE(p.inventory_head->crop_name == "Mint");
    REQUIRE(p.inventory_head->quantity == 5);

    // add some crop, quantity increase
    add_to_inventory(p, mint, 3);
    REQUIRE(p.inventory_head->crop_name == "Mint");
    REQUIRE(p.inventory_head->quantity == 8);

    // add different crop
    add_to_inventory(p, wheat, 2);

    bool found_wheat = false;
    inventory_node *cur = p.inventory_head;
    while(cur != nullptr)
    {
        if (cur->crop_name == "Wheat" && cur->quantity == 2) found_wheat = true;
        cur = cur->next;
    }
    REQUIRE(found_wheat == true);
}

TEST_CASE("Inventory - remove_from_inventory decreases quantity and removes node when qty reaches 0")
{
    player_data p;
    p.player_name = "Test";
    p.inventory_head = nullptr;
    p.level = 1;
    p.coin = 0;
    p.hp = 100;
    p.total_planted_crops = 0;

    crop_data mint = create_crop("Mint", 10, 6);

    add_to_inventory(p, mint, 5);

    SECTION("Removing part of the quantity succeeds and keeps node")
    {
        bool ok = remove_from_inventory(p, "Mint", 2);
        REQUIRE(ok == true);
        REQUIRE(p.inventory_head != nullptr);
        REQUIRE(p.inventory_head->crop_name == "Mint");
        REQUIRE(p.inventory_head->quantity == 3);
    }

    SECTION("Removing exact remaining quantity removes the node")
    {
        bool ok = remove_from_inventory(p, "Mint", 5);
        REQUIRE(ok == true);
        REQUIRE(p.inventory_head == nullptr);
    }
}