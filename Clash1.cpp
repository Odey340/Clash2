#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <sstream>

// Helpers
static inline std::string to_lower_trim(const std::string &s) {
    size_t start = 0;
    while (start < s.size() && std::isspace((unsigned char)s[start])) ++start;
    size_t end = s.size();
    while (end > start && std::isspace((unsigned char)s[end - 1])) --end;
    std::string out;
    out.reserve(end - start);
    for (size_t i = start; i < end; ++i) out.push_back(std::tolower((unsigned char)s[i]));
    return out;
}

int main() {
    // Try to load ordered card list from cards.txt (one card per line).
    std::vector<std::string> cards;
    std::ifstream in("cards.txt");
    if (in) {
        std::string line;
        while (std::getline(in, line)) {
            std::string t = to_lower_trim(line);
            if (!t.empty()) cards.push_back(line); // preserve original case in vector
        }
        std::cout << "Loaded " << cards.size() << " cards from cards.txt\n";
    } else {
        // Fallback sample list. Replace or create cards.txt to include every card in ranked order.
        cards = {
            "Barbarian Hut",
            "Cannon Cart",
            "Mega Knight",
            "Elite Barbarians",
            "Royal Recruits",
            "Prince",
            "Royal Delivery",
            "Bandit",
            "Mini Pekka",
            "Dark Prince",
            "Battle Ram",
            "Barbarian Barrel",
            "The Log",
            "Musketeer",
            "Witch",
            "Bowler",
            "Minion Horde",
            "Zappies",
            "Dart Goblin",
            "Firecracker",
            "Flying Machine",
            "Goblin Gang",
            "Fireball",
            "Lightning",
            "Poison",
            "Lumberjack",
            "Knight",
            "Pekka",
            "Giant",
            "Goblin Giant",
            "Hog Rider",
            "Royal Hogs",
            "Valkyrie",
            "Guards",
            "Minions",
            "Earthquake",
            "Ram Rider",
            "Golem",
            "Royal Giant",
            "Excecutioner",
            "Hunter",
            "Electro Wizard",
            "Skeleton Barrel",
            "Goblins",
            "Tombstone",
            "Goblin Cage",
            "Royal Ghost",
            "Electro Giant",
            "Barbarians",
            "Bomb Tower",
            "Inferno Dragon",
            "Electro Dragon",
            "Phoenix",
            "Mortar",
            "Balloon",
            "Cannon",
            "Rocket",
            "Battle Healer",
            "Goblin Drill",
            "Night Witch",
            "Inferno Tower",
            "Tesla",
            "Elixir Collector",
            "Rage",
            "X-Bow",
            "Ice Golem",
            "Fisherman",
            "Void",
            "Lava Hound",
            "Tornado",
            "Miner",
            "Graveyard",
            



            // ... add or load the full list here
        };
        std::cout << "Using built-in sample list (" << cards.size() << " cards). Put full ranked list in cards.txt to use it.\n";
    }

    if (cards.empty()) {
        std::cerr << "No cards available. Please provide a cards.txt with one card name per line.\n";
        return 1;
    }

    // Build map: lowercase name -> rank (1-based)
    std::unordered_map<std::string, int> rank;
    rank.reserve(cards.size());
    for (size_t i = 0; i < cards.size(); ++i) {
        rank[to_lower_trim(cards[i])] = static_cast<int>(i) + 1;
    }

    auto read_choice = [&](int n) -> std::string {
        std::string input;
        std::cout << "Enter card choice #" << n << ": ";
        std::getline(std::cin, input);
        return to_lower_trim(input);
    };

    // Read three choices
    std::vector<std::string> choices(3);
    for (int i = 0; i < 3; ++i) {
        choices[i] = read_choice(i + 1);
        if (choices[i].empty()) {
            std::cout << "Empty input; please enter a card name.\n";
            --i;
        }
    }

    // Validate and find lowest rank
    int bestRank = INT_MAX;
    int bestIndex = -1;
    for (int i = 0; i < 3; ++i) {
        auto it = rank.find(choices[i]);
        if (it == rank.end()) {
            std::cerr << "Card not found: \"" << choices[i] << "\". Make sure names match entries in cards.txt (case-insensitive).\n";
            return 1;
        }
        if (it->second < bestRank) {
            bestRank = it->second;
            bestIndex = static_cast<int>(i);
        }
    }

    std::cout << "Best (lowest-ranked) choice: " << cards[bestRank - 1] << " (rank " << bestRank << ")\n";
    return 0;
}