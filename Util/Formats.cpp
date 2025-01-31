#include <Formats.h>

#include <sstream>
#include <unordered_map>

std::unordered_map<std::string, std::string> targetAliases = {
        { "nearest", "@p" },
        { "everything", "@e" },
        { "everyone", "@a" },
        { "random", "@r" },
        { "self", "@s" },
};

const std::string validItemsOrBlocks[] = {
        "minecraft:air",
        "minecraft:stone",
        "minecraft:grass",
        "minecraft:dirt",
        "minecraft:cobblestone",
        "minecraft:planks",
        "minecraft:sapling",
        "minecraft:bedrock",
        "minecraft:flowing_water",
        "minecraft:water",
        "minecraft:flowing_lava",
        "minecraft:lava",
        "minecraft:sand",
        "minecraft:sand",
        "minecraft:gravel",
        "minecraft:gold_ore",
        "minecraft:iron_ore",
        "minecraft:coal_ore",
        "minecraft:log",
        "minecraft:leaves",
        "minecraft:sponge",
        "minecraft:glass",
        "minecraft:lapis_ore",
        "minecraft:lapis_block",
        "minecraft:dispenser",
        "minecraft:sandstone",
        "minecraft:noteblock",
        "minecraft:bed",
        "minecraft:golden_rail",
        "minecraft:detector_rail",
        "minecraft:sticky_piston",
        "minecraft:web",
        "minecraft:tallgrass",
        "minecraft:deadbush",
        "minecraft:piston",
        "minecraft:piston_head",
        "minecraft:wool",
        "minecraft:yellow_flower",
        "minecraft:red_flower",
        "minecraft:brown_mushroom",
        "minecraft:red_mushroom",
        "minecraft:gold_block",
        "minecraft:iron_block",
        "minecraft:double_stone_slab",
        "minecraft:stone_slab",
        "minecraft:brick_block",
        "minecraft:tnt",
        "minecraft:bookshelf",
        "minecraft:mossy_cobblestone",
        "minecraft:obsidian",
        "minecraft:torch",
        "minecraft:fire",
        "minecraft:mob_spawner",
        "minecraft:oak_stairs",
        "minecraft:chest",
        "minecraft:redstone_wire",
        "minecraft:diamond_ore",
        "minecraft:diamond_block",
        "minecraft:crafting_table",
        "minecraft:wheat",
        "minecraft:farmland",
        "minecraft:furnace",
        "minecraft:lit_furnace",
        "minecraft:standing_sign",
        "minecraft:wooden_door",
        "minecraft:ladder",
        "minecraft:rail",
        "minecraft:stone_stairs",
        "minecraft:wall_sign",
        "minecraft:lever",
        "minecraft:stone_pressure_plate",
        "minecraft:iron_door",
        "minecraft:wooden_pressure_plate",
        "minecraft:redstone_ore",
        "minecraft:lit_redstone_ore",
        "minecraft:unlit_redstone_torch",
        "minecraft:redstone_torch",
        "minecraft:stone_button",
        "minecraft:snow_layer",
        "minecraft:ice",
        "minecraft:snow",
        "minecraft:cactus",
        "minecraft:clay",
        "minecraft:reeds",
        "minecraft:jukebox",
        "minecraft:fence",
        "minecraft:pumpkin",
        "minecraft:netherrack",
        "minecraft:soul_sand",
        "minecraft:glowstone",
        "minecraft:portal",
        "minecraft:lit_pumpkin",
        "minecraft:cake",
        "minecraft:unpowered_repeater",
        "minecraft:powered_repeater",
        "minecraft:stained_glass",
        "minecraft:trapdoor",
        "minecraft:monster_egg",
        "minecraft:stonebrick",
        "minecraft:brown_mushroom_block",
        "minecraft:red_mushroom_block",
        "minecraft:iron_bars",
        "minecraft:glass_pane",
        "minecraft:melon_block",
        "minecraft:pumpkin_stem",
        "minecraft:melon_stem",
        "minecraft:vine",
        "minecraft:fence_gate",
        "minecraft:brick_stairs",
        "minecraft:stone_brick_stairs",
        "minecraft:mycelium",
        "minecraft:waterlily",
        "minecraft:nether_brick",
        "minecraft:nether_brick_fence",
        "minecraft:nether_brick_stairs",
        "minecraft:nether_wart",
        "minecraft:enchanting_table",
        "minecraft:brewing_stand",
        "minecraft:cauldron",
        "minecraft:end_portal",
        "minecraft:end_portal_frame",
        "minecraft:end_stone",
        "minecraft:dragon_egg",
        "minecraft:redstone_lamp",
        "minecraft:lit_redstone_lamp",
        "minecraft:double_wooden_slab",
        "minecraft:wooden_slab",
        "minecraft:cocoa",
        "minecraft:sandstone_stairs",
        "minecraft:emerald_ore",
        "minecraft:ender_chest",
        "minecraft:tripwire_hook",
        "minecraft:tripwire_hook",
        "minecraft:emerald_block",
        "minecraft:spruce_stairs",
        "minecraft:birch_stairs",
        "minecraft:jungle_stairs",
        "minecraft:command_block",
        "minecraft:beacon",
        "minecraft:cobblestone_wall",
        "minecraft:flower_pot",
        "minecraft:carrots",
        "minecraft:potatoes",
        "minecraft:wooden_button",
        "minecraft:skull",
        "minecraft:anvil",
        "minecraft:trapped_chest",
        "minecraft:light_weighted_pressure_plate",
        "minecraft:heavy_weighted_pressure_plate",
        "minecraft:unpowered_comparator",
        "minecraft:powered_comparator",
        "minecraft:daylight_detector",
        "minecraft:redstone_block",
        "minecraft:quartz_ore",
        "minecraft:hopper",
        "minecraft:quartz_block",
        "minecraft:quartz_stairs",
        "minecraft:activator_rail",
        "minecraft:dropper",
        "minecraft:stained_hardened_clay",
        "minecraft:stained_glass_pane",
        "minecraft:leaves2",
        "minecraft:log2",
        "minecraft:acacia_stairs",
        "minecraft:dark_oak_stairs",
        "minecraft:slime",
        "minecraft:barrier",
        "minecraft:iron_trapdoor",
        "minecraft:prismarine",
        "minecraft:sea_lantern",
        "minecraft:hay_block",
        "minecraft:carpet",
        "minecraft:hardened_clay",
        "minecraft:coal_block",
        "minecraft:packed_ice",
        "minecraft:double_plant",
        "minecraft:standing_banner",
        "minecraft:wall_banner",
        "minecraft:daylight_detector_inverted",
        "minecraft:red_sandstone",
        "minecraft:red_sandstone_stairs",
        "minecraft:double_stone_slab2",
        "minecraft:stone_slab2",
        "minecraft:spruce_fence_gate",
        "minecraft:birch_fence_gate",
        "minecraft:jungle_fence_gate",
        "minecraft:dark_oak_fence_gate",
        "minecraft:acacia_fence_gate",
        "minecraft:spruce_fence",
        "minecraft:birch_fence",
        "minecraft:jungle_fence",
        "minecraft:dark_oak_fence",
        "minecraft:acacia_fence",
        "minecraft:spruce_door",
        "minecraft:birch_door",
        "minecraft:jungle_door",
        "minecraft:acacia_door",
        "minecraft:dark_oak_door",
        "minecraft:end_rod",
        "minecraft:chorus_plant",
        "minecraft:chorus_flower",
        "minecraft:purpur_block",
        "minecraft:purpur_pillar",
        "minecraft:purpur_stairs",
        "minecraft:purpur_double_slab",
        "minecraft:purpur_slab",
        "minecraft:end_bricks",
        "minecraft:beetroots",
        "minecraft:grass_path",
        "minecraft:end_gateway",
        "minecraft:repeating_command_block",
        "minecraft:chain_command_block",
        "minecraft:frosted_ice",
        "minecraft:magma",
        "minecraft:nether_wart_block",
        "minecraft:red_nether_brick",
        "minecraft:bone_block",
        "minecraft:structure_void",
        "minecraft:observer",
        "minecraft:white_shulker_box",
        "minecraft:orange_shulker_box",
        "minecraft:magenta_shulker_box",
        "minecraft:light_blue_shulker_box",
        "minecraft:yellow_shulker_box",
        "minecraft:lime_shulker_box",
        "minecraft:pink_shulker_box",
        "minecraft:gray_shulker_box",
        "minecraft:silver_shulker_box",
        "minecraft:cyan_shulker_box",
        "minecraft:purple_shulker_box",
        "minecraft:blue_shulker_box",
        "minecraft:brown_shulker_box",
        "minecraft:green_shulker_box",
        "minecraft:red_shulker_box",
        "minecraft:black_shulker_box",
        "minecraft:white_glazed_terracotta",
        "minecraft:orange_glazed_terracotta",
        "minecraft:magenta_glazed_terracotta",
        "minecraft:light_blue_glazed_terracotta",
        "minecraft:yellow_glazed_terracotta",
        "minecraft:lime_glazed_terracotta",
        "minecraft:pink_glazed_terracotta",
        "minecraft:gray_glazed_terracotta",
        "minecraft:light_gray_glazed_terracotta",
        "minecraft:cyan_glazed_terracotta",
        "minecraft:purple_glazed_terracotta",
        "minecraft:blue_glazed_terracotta",
        "minecraft:brown_glazed_terracotta",
        "minecraft:green_glazed_terracotta",
        "minecraft:red_glazed_terracotta",
        "minecraft:black_glazed_terracotta",
        "minecraft:concrete",
        "minecraft:concrete_powder",
        "minecraft:structure_block",
        "minecraft:iron_shovel",
        "minecraft:iron_pickaxe",
        "minecraft:iron_axe",
        "minecraft:flint_and_steel",
        "minecraft:apple",
        "minecraft:bow",
        "minecraft:arrow",
        "minecraft:coal",
        "minecraft:diamond",
        "minecraft:iron_ingot",
        "minecraft:gold_ingot",
        "minecraft:iron_sword",
        "minecraft:wooden_sword",
        "minecraft:wooden_shovel",
        "minecraft:wooden_pickaxe",
        "minecraft:wooden_axe",
        "minecraft:stone_sword",
        "minecraft:stone_shovel",
        "minecraft:stone_pickaxe",
        "minecraft:stone_axe",
        "minecraft:diamond_sword",
        "minecraft:diamond_shovel",
        "minecraft:diamond_pickaxe",
        "minecraft:diamond_axe",
        "minecraft:stick",
        "minecraft:bowl",
        "minecraft:mushroom_stew",
        "minecraft:golden_sword",
        "minecraft:golden_shovel",
        "minecraft:golden_pickaxe",
        "minecraft:golden_axe",
        "minecraft:string",
        "minecraft:feather",
        "minecraft:gunpowder",
        "minecraft:wooden_hoe",
        "minecraft:stone_hoe",
        "minecraft:iron_hoe",
        "minecraft:diamond_hoe",
        "minecraft:golden_hoe",
        "minecraft:wheat_seeds",
        "minecraft:wheat",
        "minecraft:bread",
        "minecraft:leather_helmet",
        "minecraft:leather_chestplate",
        "minecraft:leather_leggings",
        "minecraft:leather_boots",
        "minecraft:chainmail_helmet",
        "minecraft:chainmail_chestplate",
        "minecraft:chainmail_leggings",
        "minecraft:chainmail_boots",
        "minecraft:iron_helmet",
        "minecraft:iron_chestplate",
        "minecraft:iron_leggings",
        "minecraft:iron_boots",
        "minecraft:diamond_helmet",
        "minecraft:diamond_chestplate",
        "minecraft:diamond_leggings",
        "minecraft:diamond_boots",
        "minecraft:golden_helmet",
        "minecraft:golden_chestplate",
        "minecraft:golden_leggings",
        "minecraft:golden_boots",
        "minecraft:flint",
        "minecraft:porkchop",
        "minecraft:cooked_porkchop",
        "minecraft:painting",
        "minecraft:golden_apple",
        "minecraft:sign",
        "minecraft:wooden_door",
        "minecraft:bucket",
        "minecraft:water_bucket",
        "minecraft:lava_bucket",
        "minecraft:minecart",
        "minecraft:saddle",
        "minecraft:iron_door",
        "minecraft:redstone",
        "minecraft:snowball",
        "minecraft:boat",
        "minecraft:leather",
        "minecraft:milk_bucket",
        "minecraft:brick",
        "minecraft:clay_ball",
        "minecraft:reeds",
        "minecraft:paper",
        "minecraft:book",
        "minecraft:slime_ball",
        "minecraft:chest_minecart",
        "minecraft:furnace_minecart",
        "minecraft:egg",
        "minecraft:compass",
        "minecraft:fishing_rod",
        "minecraft:clock",
        "minecraft:glowstone_dust",
        "minecraft:fish",
        "minecraft:cooked_fish",
        "minecraft:cooked_fish",
        "minecraft:dye",
        "minecraft:bone",
        "minecraft:sugar",
        "minecraft:cake",
        "minecraft:bed",
        "minecraft:repeater",
        "minecraft:cookie",
        "minecraft:filled_map",
        "minecraft:shears",
        "minecraft:melon",
        "minecraft:pumpkin_seeds",
        "minecraft:melon_seeds",
        "minecraft:beef",
        "minecraft:cooked_beef",
        "minecraft:chicken",
        "minecraft:cooked_chicken",
        "minecraft:rotten_flesh",
        "minecraft:ender_pearl",
        "minecraft:blaze_rod",
        "minecraft:ghast_tear",
        "minecraft:gold_nugget",
        "minecraft:nether_wart",
        "minecraft:potion",
        "minecraft:glass_bottle",
        "minecraft:spider_eye",
        "minecraft:fermented_spider_eye",
        "minecraft:blaze_powder",
        "minecraft:magma_cream",
        "minecraft:brewing_stand",
        "minecraft:cauldron",
        "minecraft:ender_eye",
        "minecraft:speckled_melon",
        "minecraft:spawn_egg",
        "minecraft:experience_bottle",
        "minecraft:fire_charge",
        "minecraft:writable_book",
        "minecraft:written_book",
        "minecraft:emerald",
        "minecraft:item_frame",
        "minecraft:flower_pot",
        "minecraft:carrot",
        "minecraft:potato",
        "minecraft:baked_potato",
        "minecraft:poisonous_potato",
        "minecraft:map",
        "minecraft:golden_carrot",
        "minecraft:skull",
        "minecraft:skull",
        "minecraft:skull",
        "minecraft:skull",
        "minecraft:skull",
        "minecraft:skull",
        "minecraft:carrot_on_a_stick",
        "minecraft:nether_star",
        "minecraft:pumpkin_pie",
        "minecraft:fireworks",
        "minecraft:firework_charge",
        "minecraft:enchanted_book",
        "minecraft:comparator",
        "minecraft:netherbrick",
        "minecraft:quartz",
        "minecraft:tnt_minecart",
        "minecraft:hopper_minecart",
        "minecraft:prismarine_shard",
        "minecraft:prismarine_crystals",
        "minecraft:rabbit",
        "minecraft:cooked_rabbit",
        "minecraft:rabbit_stew",
        "minecraft:rabbit_foot",
        "minecraft:rabbit_hide",
        "minecraft:armor_stand",
        "minecraft:iron_horse_armor",
        "minecraft:golden_horse_armor",
        "minecraft:diamond_horse_armor",
        "minecraft:lead",
        "minecraft:name_tag",
        "minecraft:command_block_minecart",
        "minecraft:mutton",
        "minecraft:cooked_mutton",
        "minecraft:banner",
        "minecraft:end_crystal",
        "minecraft:spruce_door",
        "minecraft:birch_door",
        "minecraft:jungle_door",
        "minecraft:acacia_door",
        "minecraft:dark_oak_door",
        "minecraft:chorus_fruit",
        "minecraft:popped_chorus_fruit",
        "minecraft:beetroot",
        "minecraft:beetroot_seeds",
        "minecraft:beetroot_soup",
        "minecraft:dragon_breath",
        "minecraft:splash_potion",
        "minecraft:spectral_arrow",
        "minecraft:tipped_arrow",
        "minecraft:lingering_potion",
        "minecraft:shield",
        "minecraft:elytra",
        "minecraft:spruce_boat",
        "minecraft:birch_boat",
        "minecraft:jungle_boat",
        "minecraft:acacia_boat",
        "minecraft:dark_oak_boat",
        "minecraft:totem_of_undying",
        "minecraft:shulker_shell",
        "minecraft:iron_nugget",
        "minecraft:knowledge_book",
        "minecraft:record_13",
        "minecraft:record_cat",
        "minecraft:record_blocks",
        "minecraft:record_chirp",
        "minecraft:record_far",
        "minecraft:record_mall",
        "minecraft:record_mellohi",
        "minecraft:record_stal",
        "minecraft:record_strad",
        "minecraft:record_ward",
        "minecraft:record_11",
        "minecraft:record_wait",
};

const std::string validEntities[] = {
        "minecraft:item",
        "minecraft:xp_orb",
        "minecraft:area_effect_cloud",
        "minecraft:elder_guardian",
        "minecraft:wither_skeleton",
        "minecraft:stray",
        "minecraft:egg",
        "minecraft:leash_knot",
        "minecraft:painting",
        "minecraft:arrow",
        "minecraft:snowball",
        "minecraft:fireball",
        "minecraft:small_fireball",
        "minecraft:ender_pearl",
        "minecraft:eye_of_ender_signal",
        "minecraft:potion",
        "minecraft:xp_bottle",
        "minecraft:item_frame",
        "minecraft:wither_skull",
        "minecraft:tnt",
        "minecraft:falling_block",
        "minecraft:fireworks_rocket",
        "minecraft:husk",
        "minecraft:spectral_arrow",
        "minecraft:shulker_bullet",
        "minecraft:dragon_fireball",
        "minecraft:zombie_villager",
        "minecraft:skeleton_horse",
        "minecraft:zombie_horse",
        "minecraft:armor_stand",
        "minecraft:donkey",
        "minecraft:mule",
        "minecraft:evocation_fangs",
        "minecraft:evocation_illager",
        "minecraft:vex",
        "minecraft:vindication_illager",
        "minecraft:illusion_illager",
        "minecraft:commandblock_minecart",
        "minecraft:boat",
        "minecraft:minecart",
        "minecraft:chest_minecart",
        "minecraft:furnace_minecart",
        "minecraft:tnt_minecart",
        "minecraft:hopper_minecart",
        "minecraft:spawner_minecart",
        "minecraft:creeper",
        "minecraft:skeleton",
        "minecraft:spider",
        "minecraft:giant",
        "minecraft:zombie",
        "minecraft:slime",
        "minecraft:ghast",
        "minecraft:zombie_pigman",
        "minecraft:enderman",
        "minecraft:cave_spider",
        "minecraft:silverfish",
        "minecraft:blaze",
        "minecraft:magma_cube",
        "minecraft:ender_dragon",
        "minecraft:wither",
        "minecraft:bat",
        "minecraft:witch",
        "minecraft:endermite",
        "minecraft:guardian",
        "minecraft:shulker",
        "minecraft:pig",
        "minecraft:sheep",
        "minecraft:cow",
        "minecraft:chicken",
        "minecraft:squid",
        "minecraft:wolf",
        "minecraft:mooshroom",
        "minecraft:snowman",
        "minecraft:ocelot",
        "minecraft:villager_golem",
        "minecraft:horse",
        "minecraft:rabiit",
        "minecraft:polar_bear",
        "minecraft:llama",
        "minecraft:llama_spit",
        "minecraft:parrot",
        "minecraft:villager",
        "minecraft:ender_crystal",
};

const std::string minecraft = "minecraft:";

bool isItemOrBlock(const std::string &target) {
    return std::find(std::begin(validItemsOrBlocks), std::end(validItemsOrBlocks), parseMinecraft(target))
        != std::end(validItemsOrBlocks);
}

std::string parseTarget(const std::string &target) {
    if (targetAliases.find(target) != targetAliases.end()) return targetAliases[target];
    return target;
}

std::string parseMinecraft(const std::string &target) {
    if (target.substr(0, minecraft.size()) != minecraft) return minecraft + target;
    return target;
}

std::string parseItemOrBlock(const std::string &item) {
    std::string result = parseMinecraft(item);
    if (std::find(std::begin(validItemsOrBlocks), std::end(validItemsOrBlocks), result)
        == std::end(validItemsOrBlocks)) {
        throw InvalidParam("item or block", item);
    }
    return result;
}

std::string parseEntity(const std::string &entity) {
    std::string result = parseMinecraft(entity);
    if (std::find(std::begin(validEntities), std::end(validEntities), result)
        == std::end(validEntities)) {
        throw InvalidParam("entity", entity);
    }
    return result;
}

std::string parseQuotes(const std::string &text) {
    // TODO: Fill in with cool stuff, e.g. escapes and take Parser object instead.
    return text.substr(1, text.size() - 2);
}

std::string parseName(const std::string &text) {
    std::stringstream stream;
    bool first = true;
    for (char a : text) {
        if (std::isupper(a)) {
            if (!first) {
                stream << "_";
            }
            stream << (char)std::tolower(a);
        } else {
            stream << a;
        }
        if (first) first = false;
    }
    return stream.str();
}
