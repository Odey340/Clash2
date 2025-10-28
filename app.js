// Load card rankings from the C++ program's built-in list
const cards = [
    "Barbarian Hut", "Cannon Cart", "Mega Knight", "Elite Barbarians", "Royal Recruits",
    "Prince", "Royal Delivery", "Bandit", "Mini Pekka", "Dark Prince", "Battle Ram",
    "Barbarian Barrel", "The Log", "Musketeer", "Witch", "Bowler", "Minion Horde",
    "Zappies", "Dart Goblin", "Firecracker", "Flying Machine", "Goblin Gang", "Fireball",
    "Lightning", "Poison", "Lumberjack", "Knight", "Pekka", "Giant", "Goblin Giant",
    "Hog Rider", "Royal Hogs", "Valkyrie", "Guards", "Minions", "Earthquake", "Ram Rider",
    "Golem", "Royal Giant", "Excecutioner", "Hunter", "Electro Wizard", "Skeleton Barrel",
    "Goblins", "Tombstone", "Goblin Cage", "Royal Ghost", "Electro Giant", "Barbarians",
    "Bomb Tower", "Inferno Dragon", "Electro Dragon", "Phoenix", "Mortar", "Balloon",
    "Cannon", "Rocket", "Battle Healer", "Goblin Drill", "Night Witch", "Inferno Tower",
    "Tesla", "Elixir Collector", "Rage", "X-Bow", "Ice Golem", "Fisherman", "Void",
    "Lava Hound", "Tornado", "Miner", "Graveyard"
];

// Initialize elixir tracking
let currentElixir = 5;
const maxElixir = 10;
const elixirGainInterval = 2800; // 2.8 seconds

// DOM Elements
const elixirAmount = document.getElementById('elixir-amount');
const elixirFill = document.getElementById('elixir-fill');
const analyzeBtn = document.getElementById('analyze-btn');
const result = document.getElementById('result');
const cardList = document.getElementById('card-list');

// Populate datalist with card options
function initializeCardList() {
    cards.forEach(card => {
        const option = document.createElement('option');
        option.value = card;
        cardList.appendChild(option);
    });
}

// Update elixir display
function updateElixirDisplay() {
    elixirAmount.textContent = currentElixir;
    const fillPercent = (currentElixir / maxElixir) * 100;
    elixirFill.style.width = `${fillPercent}%`;
}

// Start elixir gain timer
function startElixirGain() {
    setInterval(() => {
        if (currentElixir < maxElixir) {
            currentElixir = Math.min(maxElixir, currentElixir + 1);
            updateElixirDisplay();
        }
    }, elixirGainInterval);
}

// Find best card among choices
function findBestCard(choices) {
    let bestRank = Infinity;
    let bestCard = null;

    choices.forEach(choice => {
        const index = cards.findIndex(card => 
            card.toLowerCase() === choice.toLowerCase());
        
        if (index !== -1 && index < bestRank) {
            bestRank = index;
            bestCard = cards[index];
        }
    });

    return { card: bestCard, rank: bestRank + 1 };
}

// Analyze button click handler
analyzeBtn.addEventListener('click', () => {
    const card1 = document.getElementById('card1').value.trim();
    const card2 = document.getElementById('card2').value.trim();
    const card3 = document.getElementById('card3').value.trim();

    if (!card1 || !card2 || !card3) {
        result.textContent = 'Please enter all three cards';
        result.classList.remove('highlight');
        return;
    }

    const choices = [card1, card2, card3];
    const invalid = choices.filter(choice => 
        !cards.find(card => card.toLowerCase() === choice.toLowerCase()));

    if (invalid.length > 0) {
        result.textContent = `Invalid card name(s): ${invalid.join(', ')}`;
        result.classList.remove('highlight');
        return;
    }

    const best = findBestCard(choices);
    result.innerHTML = `
        Best card to play: <strong>${best.card}</strong><br>
        (Rank: ${best.rank} out of ${cards.length})
    `;
    result.classList.add('highlight');
});

// Initialize
initializeCardList();
startElixirGain();
updateElixirDisplay();