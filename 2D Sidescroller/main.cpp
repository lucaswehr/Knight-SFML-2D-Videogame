#include "Animation.hpp"
#include "Knight.hpp"
#include "Tile.hpp"
#include "wolf.hpp"
#include "Enemy.hpp"
#include "Skeleton.hpp"
#include "Arrow.hpp"
#include "Dragon.hpp"
#include "text.hpp"
#include "Healthbar.hpp"


enum class gameState
{
    mainMenu,
    playing,
    paused,
    howtoPlay,
    gameOver,
    level1Pause,
    end


};

int main()
{
    std::srand(std::time(0));

    gameState gameState = gameState::mainMenu;

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktopMode, "Knight Game", sf::Style::Default, sf::State::Fullscreen);
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(false);

    sf::View view(sf::FloatRect({ 0, 0 }, { 1920, 1080 }));

    view.setSize({ 1920, 1080 });

    int windowWidth = 1920;
    int windowHeight = 1080;
    const float margin = 200.f;
   
    window.setFramerateLimit(60);
    sf::Clock clock;

    sf::Clock levelDelay;
    sf::Time levelTime = sf::seconds(3);

    sf::Clock deathDelay;
    sf::Time deathTime = sf::seconds(2);

    sf::Clock backToMenuDelay;
    sf::Time backToMenuTime = sf::seconds(5);

    sf::Clock endDelay;
    sf::Time endTime = sf::seconds(5);

    sf::Clock endDelayToMenu;
    sf::Time endTimeToMenu = sf::seconds(5);

    sf::Font font;
    if (!font.openFromFile("OldLondon.ttf"))
    {
        std::cout << "Error" << std::endl;

        return 0;

    }

    std::string fontText = "OldLondon.ttf";

    Text title(fontText, "The Last Paladin", 300.f, 60.f, sf::Color::White, 200);
    Text play(fontText, "Play", 830.f, 400.f, sf::Color::White, 130);
    Text howToPlay(fontText, "How To Play", 620.f, 600.f, sf::Color::White, 130);
    Text exit(fontText, "Exit", 830.f, 800.f, sf::Color::White, 130);
    Text levelOne(fontText, "Zone 1: ", 780.f, 450.f, sf::Color::White, 130);
    Text Menu(fontText, "Menu", 1600.f, 900.f, sf::Color::White, 130);

    Text howToPlay2(fontText, "How To Play:", 600.f, 0.f, sf::Color::White, 130);
    Text rules(fontText, "walk: A/D      Jump: Space    Run: walk + LShift   Attack: LClick", 75.f, 400.f, sf::Color::White, 70);
    Text rules2(fontText, "Block: S      Roll: RClick    Hang: Space     Heal: R", 75.f, 800.f, sf::Color::White, 70);

    
    Healthbar healthBar(500,40);

    sf::Music menuMusic;
    menuMusic.openFromFile("Sounds/Kings_Feast.mp3");
    menuMusic.setLooping(true);
    menuMusic.play();
    bool playSong = true;
    bool playSong2 = true;
    bool playSong3 = true;
    bool playSong4 = true;
    bool playMenuSound = false;
    bool playMenuSound2 = false;
    bool playMenuSound3 = false;
    bool playMenuSound4 = false;
    
    bool playMenuClick = false;
    bool playMenuClick2 = false;
    bool playMenuClick3 = false;
    bool playMenuClick4 = false;

    sf::Texture inventoryText;
    if (!inventoryText.loadFromFile("Inventory.png"))
    {
        std::cout << "error loading the knight inventory sprite" << std::endl;
    }

    sf::Sprite inventory(inventoryText);

    inventory.setTextureRect(sf::IntRect({ 3 * 28, 5 * 32 }, { 32, 32 }));
    inventory.setScale({ 5, 7 });

    sf::Texture bannerText;
    if (!bannerText.loadFromFile("Banners.png"))
    {
        std::cout << "error loading the knight banner sprite" << std::endl;
    }

    sf::Sprite banner(bannerText);
    sf::Sprite banner2(bannerText);
    sf::Sprite banner3(bannerText);
    sf::Sprite banner4(bannerText);
    sf::Sprite banner5(bannerText);
    sf::Sprite banner6(bannerText);
    sf::Sprite banner7(bannerText);
    sf::Sprite banner8(bannerText);


    banner.setTextureRect(sf::IntRect({ 3 * 27, 7 *32 }, { 32, 32 }));
    banner.setScale({ 8, 8 });
    banner.setPosition({ 300,50 });

    banner2.setTextureRect(sf::IntRect({ 2 * 32, 7 * 32 }, { 32, 32 }));
    banner2.setScale({ 8, 8 });
    banner2.setPosition({ 200,50 });

    banner3.setTextureRect(sf::IntRect({ 3 * 27, 7 * 32 }, { 32, 32 }));
    banner3.setScale({ 8, 8 });
    banner3.setPosition({ 550,50 });

    banner4.setTextureRect(sf::IntRect({ 3 * 27, 7 * 32 }, { 32, 32 }));
    banner4.setScale({ 8, 8 });
    banner4.setPosition({ 800,50 });

    banner5.setTextureRect(sf::IntRect({ 3 * 27, 7 * 32 }, { 32, 32 }));
    banner5.setScale({ 8, 8 });
    banner5.setPosition({ 1050,50 });

    banner6.setTextureRect(sf::IntRect({ 3 * 27, 7 * 32 }, { 32, 32 }));
    banner6.setScale({ 8, 8 });
    banner6.setPosition({ 1300,50 });

    banner7.setTextureRect(sf::IntRect({ 3 * 32, 7 * 32 }, { 32, 32 }));
    banner7.setScale({ 8, 8 });
    banner7.setPosition({ 1450, 50 });

    sf::Texture heartTexture;
    if (!heartTexture.loadFromFile("Knight_1/heartSprite.png"))
    {
        std::cout << "error loading the knight  sprite" << std::endl;
    }

    sf::Sprite heartSprite(heartTexture);
    heartSprite.setScale({ 2.5,2.5 });

    sf::Texture text;
    if (!text.loadFromFile("Knight_1/Idle.png"))
    {
        std::cout << "error loading the knight idle sprite" << std::endl;
    }

    sf::Texture text2;
    if (!text2.loadFromFile("Knight_1/Walk.png"))
    {
        std::cout << "error loading the knight walk sprite" << std::endl;
    }

    sf::Texture text3;
    if (!text3.loadFromFile("Knight_1/Jump.png"))
    {
        std::cout << "error loading the knight jump sprite" << std::endl;
    }

    sf::Texture attack1;
    if (!attack1.loadFromFile("Knight_1/Attack 1.png"))
    {
        std::cout << "error loading the knight attack1 sprite" << std::endl;
    }

    sf::Texture attack2;
    if (!attack2.loadFromFile("Knight_1/Attack 2.png"))
    {
        std::cout << "error loading the knight attack2 sprite" << std::endl;
    }

    sf::Texture attack3;
    if (!attack3.loadFromFile("Knight_1/Attack 3.png"))
    {
        std::cout << "error loading the knight attack3 sprite" << std::endl;
    }

    sf::Texture run;
    if (!run.loadFromFile("Knight_1/Run.png"))
    {
        std::cout << "error loading the knight run sprite" << std::endl;
    }

    sf::Texture shield;
    if (!shield.loadFromFile("Knight_1/Defend.png"))
    {
        std::cout << "error loading the knight defend sprite" << std::endl;
    }

    sf::Texture runningAttack;
    if (!runningAttack.loadFromFile("Knight_1/Run+Attack.png"))
    {
        std::cout << "error loading the knight run+attack sprite" << std::endl;
    }

    sf::Texture hurt;
    if (!hurt.loadFromFile("Knight_1/hurt.png"))
    {
        std::cout << "error loading the knight protect sprite" << std::endl;
    }

    sf::Texture knightDead;
    if (!knightDead.loadFromFile("Knight_1/Dead.png"))
    {
        std::cout << "error loading the knight dead sprite" << std::endl;
    }

    sf::Texture knightHanging;
    if (!knightHanging.loadFromFile("Knight_1/Hang.png"))
    {
        std::cout << "error loading the knight hang sprite" << std::endl;
    }


    sf::Texture knightClimbing;
    if (!knightClimbing.loadFromFile("Knight_1/Pull_up.png"))
    {
        std::cout << "error loading the knight pull up sprite" << std::endl;
    }

    sf::Texture knightRolling;
    if (!knightRolling.loadFromFile("Knight_1/Roll.png"))
    {
        std::cout << "error loading the knight roll sprite" << std::endl;
    }

    sf::Texture elixir;
    if (!elixir.loadFromFile("Knight_1/Elixir.png"))
    {
        std::cout << "error loading the knight elixir sprite" << std::endl;
    }


    sf::Texture background;
    if (!background.loadFromFile("origbig.png"))
    {
        std::cout << "error loading the background sprite" << std::endl;
    }

    sf::Texture titleBackground;
    if (!titleBackground.loadFromFile("titleBackground.png"))
    {
        std::cout << "error loading the knight titleBackground sprite" << std::endl;
    }

    sf::Texture forestBackgroundTexture;
    if (!forestBackgroundTexture.loadFromFile("forestBackground.png"))
    {
        std::cout << "error loading the knight forestbackground sprite" << std::endl;
    }

    sf::Texture trees;
    if (!trees.loadFromFile("tileset/tree.png"))
    {
        std::cout << "error loading the knight tree sprite" << std::endl;
    }

    sf::Texture rosebush;
    if (!rosebush.loadFromFile("tileset/bush.png"))
    {
        std::cout << "error loading the knight rosebush sprite" << std::endl;
    }

    sf::Texture bush;
    if (!bush.loadFromFile("tileset/grass.png"))
    {
        std::cout << "error loading the knight bush sprite" << std::endl;
    }

    sf::Texture enemy;
    if (!enemy.loadFromFile("wolf/walk.png"))
    {
        std::cout << "error loading the wolf walk sprite" << std::endl;
    }

    sf::Texture enemyAttack1;
    if (!enemyAttack1.loadFromFile("wolf/attack_1.png"))
    {
        std::cout << "error loading the wolf attack1 sprite" << std::endl;
    }

    sf::Texture enemyAttack2;
    if (!enemyAttack2.loadFromFile("wolf/attack_2.png"))
    {
        std::cout << "error loading the wolf attack2 sprite" << std::endl;
    }

    sf::Texture enemyAttack3;
    if (!enemyAttack3.loadFromFile("wolf/attack_3.png"))
    {
        std::cout << "error loading the wolf attack3 sprite" << std::endl;
    }

    sf::Texture dead;
    if (!dead.loadFromFile("wolf/dead.png"))
    {
        std::cout << "error loading the wolf dead sprite" << std::endl;
    }

    sf::Texture wolfHurt;
    if (!wolfHurt.loadFromFile("wolf/hurt.png"))
    {
        std::cout << "error loading the wolf hurt sprite" << std::endl;
    }

    sf::Texture SkeletonIdle;
    if (!SkeletonIdle.loadFromFile("Skeleton_Archer/Idle.png"))
    {
        std::cout << "error loading the skeleton idle sprite" << std::endl;
    }

    sf::Texture SkeletonShot1;
    if (!SkeletonShot1.loadFromFile("Skeleton_Archer/Shot_2.png"))
    {
        std::cout << "error loading the skeleton shot sprite" << std::endl;
    }

    sf::Texture arrow;
    if (!arrow.loadFromFile("Skeleton_Archer/Arrow.png"))
    {
        std::cout << "error loading the skeleton arrow sprite" << std::endl;
    }

    sf::Texture skeletonHurt;
    if (!skeletonHurt.loadFromFile("Skeleton_Archer/Hurt.png"))
    {
        std::cout << "error loading the skeleton hurt sprite" << std::endl;
    }

    sf::Texture skeletonDead;
    if (!skeletonDead.loadFromFile("Skeleton_Archer/Dead.png"))
    {
        std::cout << "error loading the skeleton dead sprite" << std::endl;
    }

    sf::Texture dragonIdle;
    if (!dragonIdle.loadFromFile("Dragon/Idle.png"))
    {
        std::cout << "error loading the dragon idle sprite" << std::endl;
    }

    sf::Texture dragonWalk;
    if (!dragonWalk.loadFromFile("Dragon/Walk.png"))
    {
        std::cout << "error loading the dragon walk sprite" << std::endl;
    }

    sf::Texture dragonAttack2;
    if (!dragonAttack2.loadFromFile("Dragon/Attack_2.png"))
    {
        std::cout << "error loading the dragon attack 2 sprite" << std::endl;
    }

    sf::Texture dragonRise;
    if (!dragonRise.loadFromFile("Dragon/Rise.png"))
    {
        std::cout << "error loading the dragon rise sprite" << std::endl;
    }

    sf::Texture dragonFlight;
    if (!dragonFlight.loadFromFile("Dragon/Flight.png"))
    {
        std::cout << "error loading the dragon flight sprite" << std::endl;
    }

    sf::Texture dragonSpecial;
    if (!dragonSpecial.loadFromFile("Dragon/Special.png"))
    {
        std::cout << "error loading the dragon special sprite" << std::endl;
    }

    sf::Texture dragonLanding;
    if (!dragonLanding.loadFromFile("Dragon/Landing.png"))
    {
        std::cout << "error loading the dragon landing sprite" << std::endl;
    }

    sf::Texture dragonHurt;
    if (!dragonHurt.loadFromFile("Dragon/Hurt.png"))
    {
        std::cout << "error loading the dragon hurt sprite" << std::endl;
    }

    sf::Texture dragonDead;
    if (!dragonDead.loadFromFile("Dragon/Dead.png"))
    {
        std::cout << "error loading the dragon dead sprite" << std::endl;
    }

    sf::Texture potionTexture;
    if (!potionTexture.loadFromFile("Knight_1/potionIcon.png"))
    {
        std::cout << "error loading the knight potion sprite" << std::endl;
    }

    sf::SoundBuffer menuSoundBuffer;
    sf::Sound menuSelectSound(menuSoundBuffer);


    sf::SoundBuffer menuClickBuffer;
    sf::Sound menuClickSound(menuClickBuffer);

    menuClickBuffer.loadFromFile("Sounds/menuClickSound.mp3");
    menuSoundBuffer.loadFromFile("Sounds/menuSelectSound.mp3");

    background.setRepeated(true);
    sf::RectangleShape backgroundShape(sf::Vector2f(windowWidth, windowHeight));
    backgroundShape.setTexture(&background);

    titleBackground.setRepeated(true);
    sf::RectangleShape titleBackgroundShape(sf::Vector2f(windowWidth, windowHeight));
    titleBackgroundShape.setTexture(&titleBackground);

    sf::Sprite forestBackground(forestBackgroundTexture);
    sf::RectangleShape forestBackgroundShape(sf::Vector2f(windowWidth, windowHeight));
    forestBackgroundShape.setTexture(&forestBackgroundTexture);

    sf::Sprite img1(titleBackground);
    sf::Sprite img2(titleBackground);
    float bgSpeed = 20.f; // pixels per second
    img1.setPosition({ 0.f,0.f });
    img2.setPosition({ (float)titleBackground.getSize().x, 0.f });


    sf::Vector2f characterPosition(windowWidth / 2.f, windowHeight / 2.f);

    view.setCenter({ windowWidth / 2.f, windowHeight / 2.f });

   
    sf::RectangleShape player(sf::Vector2f(50, 50));
    player.setFillColor(sf::Color::Red);
    player.setOrigin({ 25, 25 });

    float worldWidth = 50000.f;

    sf::Sprite town(background);
    town.setScale({ 0.9,0.9 });
    town.setPosition({ 0, -50 });
    
    
    
    Knight knight(text2, text, text3, attack1, attack2, attack3, run, shield, runningAttack, hurt, knightDead, knightHanging, knightClimbing, knightRolling, elixir, potionTexture,fontText);

    Animation knightWalkDemo(text2, 8, 1, 0.1, 0, true, true);
    Animation knightJumpDemo(text3, 6, 1, 0.15, 0, true, true);
    Animation knightSprintDemo(run, 7, 1, 0.1, 0, true, true);
    Animation knightAttackDemo(attack1, 5, 1, 0.2, 0, true, true);
    Animation knightGuardDemo(shield, 5, 1, 0.1, 0, true, true);
    Animation knightRollingDemo(knightRolling, 6, 1, 0.15, 0, true, true);
    Animation knightHangingDemo(knightHanging, 6, 1, 0.15, 0, true, true);
    Animation knightDrinkingDemo(elixir, 4, 1, 0.2, 0, true, true);
   
    sf::Texture tileTextureDemo;
    if (!tileTextureDemo.loadFromFile("tileset/tilesetgrass.png")) {
        std::cout << "Failed to load tile texture\n";
    }
    sf::Sprite tileSprite(tileTextureDemo);
   
    tileSprite.setTextureRect(sf::IntRect({ 3 * 32, 3 * 32 }, { 32, 32 }));
    tileSprite.setScale({ 3,3 });

    float t;
    float eased;
    sf::Color c;
    c = c.Red;
    sf::Color c2;
    c2 = c2.Yellow;
    sf::Color outline;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<Arrow> arrows;

  


    sf::Texture tileSet;

    tileSet.loadFromFile("tileset/tilesetgrass.png");

    sf::Vector2u tileSize(32, 32);

    std::vector<Tile> tiles;

    //loads in each tile based off the number. -1 is air
    std::vector<std::vector<int>> mapData = {

        { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,1,1,1,1,1,1,1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,                   0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,1,1,1,1,1,1,1,2,-1,-1,-1,-1,-1,-1,0,1,1,1,1,35,11,11,11,34,1,1,1,1,1,1,1,1,1,1,                                   2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20,25,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11},
        { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20,21,25,11,11,34,1,1,1,1,1,1,1,1,1,1,35,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,34,                  1,1,1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11},
        { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,1,1,2,-1,-1,-1,-1,-1,20,25,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,         12,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11},
        { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,35,34,1,1,2,-1,-1,-1,-1,-1,20,21,21,25,24,21,21,21,21,21,21,21,25,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,         12,-1,-1,-1,-1,-1,-1,0,1,1,2,-1,-1,-1,-1,-1,-1,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11},
         { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,34,1,1,1,1,2,-1,-1,-1,-1,-1,-1,-1,20,22,-1,-1,-1,-1,-1,-1,-1,20,21,25,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,         12,-1,-1,-1,-1,-1,-1,10,11,11,12,-1,-1,-1,-1,-1,-1,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11},//
        { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,1,35,11,11,11,11,11,12,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20,21,25,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,       12,-1,-1,-1,-1,-1,-1,10,11,1,1,1,2,-1,-1,-1,-1,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11},//
        { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,11,11,11,11,11,11,11,12,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20,25,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,     12,-1,-1,-1,-1,-1,-1,10,11,11,11,11,12,-1,-1,-1,-1,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11},//
        { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,34,1,1,1,1,1,1,1,1,1,2,-1,-1,0,1,1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20,21,25,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,                   12,-1,-1,-1,-1,-1,-1,10,11,11,11,11,12,-1,-1,-1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
        { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,11,11,11,11,11,11,11,11,24,21,22,-1,-1,0,1,1,1,1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20,21,21,21,25,11,11,11,11,11,11,11,11,11,11,11,11,           12,-1,-1,-1,-1,-1,-1,10,11,11,11,11,12,-1,-1,-1,20,25,11,11,11,11,11,11,11,24,21,21,21,21,21,21,21,21,21,21,21,22},
         { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,11,11,11,11,11,11,11,11,12,-1,-1,-1,-1,20,21,21,21,21,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20,25,11,11,11,11,11,11,11,11,11,11,    24,22,-1,-1,-1,-1,-1,-1,10,11,11,34,1,1,   2,-1,-1,-1,10,11,11,11,11,24,21,21,22},//
        { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,1,1,1,35,24,21,21,21,21,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,1,1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,20,21,25,11,11,11,11,11,11,11,11,             12,-1,-1,-1,-1,-1,-1,-1,10,11,11,11,11,12,-1,-1,-1,-1,10,11,24,21,21,22},
        { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,11,11,11,24,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,1,1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20,25,11,11,11,11,11,11,11,        12,-1,-1,-1,-1,-1,-1,-1,10,11,11,11,11,12,-1,-1,-1,-1,10,11,12},
           { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,34,1,1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20,25,24,22,-1,-1,-1,-1,30,31,32,-1,-1,-1,-1,-1,10,11,11,11,11,11,11,11,     12,-1,-1,-1,-1,-1,-1,-1,10,11,11,11,11,12,-1,-1,-1,0,1,1,12},
           { -1,-1,-1,0,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,24,21,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,1,1,1,1,2,-1,-1,-1,-1,20,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,11,11,11,11,11,11,11,          12,-1,-1,-1,-1,-1,-1,-1,10,11,11,11,11,12,-1,-1,-1,20,21,21,22},
           { -1,0,1,35,34,1,1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,35,11,11,11,34,1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,1,1,1,1,11,11,11,11,11,11,               12,-1,-1,-1,-1,-1,-1,-1,10,11,11,11,11,12,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
           { 1,35,24,21,21,21,25,34,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,35,11,11,11,11,11,11,34,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20,21,25,11,11,11,11,11,11,11,11,      12,-1,-1,-1,-1,-1,-1,-1,10,11,34,1,1,1,    2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,    0,1,1,1,2},
           { 24,21,22,-1,-1,-1,20,21,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,1,1,1,1,1,1,1,1,1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,2,-1,-1,0,1,1,1,1,1,1,1,1,1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,1,2,-1,-1,-1,-1,10,11,11,11,11,11,11,11,11,                             12,-1,-1,-1,-1,-1,-1,-1,10,11,11,11,11,12,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,    10,11,11,11,12},
           { 12,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,1,1,1,11,11,11,11,11,11,11,12,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,12,-1,-1,20,25,11,11,11,11,11,11,11,11,34,2,-1,-1,-1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,11,11,11,11,11,11,                      12,-1,-1,-1,-1,-1,-1,-1,10,11,11,11,11,12,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,    10,11,11,11,12},
           { 1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,1,1,1,1,1,1,11,11,11,11,11,11,11,11,12,-1,-1,-1,-1,-1,-1 -1 -1 -1 -1 -1 -1,-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,1,2,-1,-1,-1,0,1,35,12,-1,-1,-1,10,11,11,11,11,11,11,11,11,11,34,1,1,1,35,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,-1,-1,-1,-1,-1,-1,-1,10,11,11,11,34,1,1,1,1,2,-1,-1,-1,-1,-1,-1,-1,         0,35,11,11,11,12,-1,-1,-1,-1,-1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
           { 11,12,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,1,2,-1,-1,-1,0,1,1,1,1,2,-1,-1,-1,10,34,1,2,-1,-1,-1,20,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,35,11,11,11,11,11,11,11,11,11,11,11,                                                       12,-1,-1,-1,-1,-1,-1,-1,10,11,11,11,11,11,11,11,11,12,-1,-1,-1,-1,-1,-1,-1,   10,11,11,11,11,12,-1,-1,-1,-1,-1,20,25,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,24,22},
           { 11,34,1,1,1,1,1,1,1,1,1,1,1,35,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,1,1,2,-1,-1,-1,10,1,1,1,1,1,2,-1,-1,10,11,24,22,-1,-1,-1,-1,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,                       12,-1,-1,-1,-1,-1,-1,-1,10,11,11,11,11,34,1,1,1,1,1,1,1,1,1,1,1,1,1,1,35,11,12,-1,-1,-1,-1,-1,-1,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12},
           {11,11,11,11,11,11,11,11,11,11,11,11,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,-1,-1,10,11,11,12,-1,-1,-1,10,11,11,11,11,11,12,-1,-1,10,11,12,-1,-1,-1,-1,0,1,1,1,1,1,1,35,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,                                          12,-1,-1,-1,-1,-1,-1,-1,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,-1,-1,-1,-1,-1,-1,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12},
           {11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,1,1,1,1,2,-1,10,11,11,12,-1,-1,-1,0,1,1,1,1,35,12,-1,-1,0,1,2,-1,-1,-1,-1,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,                12,-1,-1,-1,-1,-1,-1,-1,10,11,11,34,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,12,-1,-1,-1,-1,-1,-1,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12},
           {21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,11,12,-1-1,10,11,11,12,-1,-1,-1,10,11,11,11,11,11,12,-1,-1,10,11,12,-1,-1,-1,-1,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11, 12,-1,-1,-1,-1,-1,-1,-1,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,-1,-1,-1,-1,-1,-1,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12}
    };

    std::vector<std::vector<int>> decorationData =
    {
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,4,1,2,3,5,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,2,3,1,5,3,4,2,1,3,2,3,2,2,3},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,2,2,3,3,3,2,-1,-1,-1,-1,-1,-1,-1,-1,3,2,3,3,-1,-1,-1,-1,-1,1,2,4,3,3,0,2,3,3},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,3,3,2,2,3,2,2,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,3,1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,4,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,4,3},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0},
        {-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,4,3,5,2,3,3,0,2,3,-1,1,2,3,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,3,1,4,3,2,3,5,3,4,2,2},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,3,5,2,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,2,2,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,3,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},

        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,3,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0},
        {-1,-1,-1,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,3,4,2,3},
        {-1,4,-1,-1,-1,1,2,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,4,3},
        {3,-1,-1,-1,-1,-1,-1,-1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,5,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,5,2},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,3,2,2,3,1,2,3,5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,5,3,-1,-1,-1,2,3,2,0,2,3,3,2,3,2},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,2,3,1,3,3,2,2,5,3,2,3},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,4,3,1,2,2,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,0,-1,-1,-1,-1,1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,4,3,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,5,2,3,3,2,1,3,3,4,2,3,2,2,5,3,3,4,1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,2,3,3,2,2,2,3,2,2,2,3,1,3,3,2,4,3,2,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,2,3,-1,-1,-1,4,1,2,3,2,-1,-1,-1,-1,-1,-1,0,3,-1,-1,-1,-1,2,3,3,0,2,1,2,2,3,3,3,2,3,3,3,2,2,3,3,2,2,2},
        {-1,-1,3,5,-1,2,3,2,2,2,0,-1,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,4,3,2,2,-1,-1,-1,-1,-1,2,2,3,3,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,4,3,2,3,5},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,2,3,-1,2,1,3,0,2,-1,3,4,3,2,3,1,2,3,3,2,3,0,2,2,5,3,2,3,2,4},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,3,3,2,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,2,4,3,2,3,3,2,2,3,2,3,2,2,2,3,2,1}


    };

    sf::Vector2u treeSize(96, 96);

    knight.loadTileMap(tileSet, mapData, tileSize, tiles);

    knight.loadDecorationMap(trees, bush, rosebush, decorationData, treeSize, tileSize);
   
    float knightOffset = 300.f;
    float lerpSpeed = 10.f; 
    sf::View defaultView = window.getDefaultView();
    bool pendingReset = false;

    knight.deathText.getText().setFillColor(sf::Color(255, 255, 255, 0)); // start invisible
    float alpha = 0.f;
    float fadeSpeed = 150.f;

    while (window.isOpen())
    {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);
        float deltaTime = clock.restart().asSeconds();
        window.clear();

        

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::MouseButtonPressed>())
            {
                const auto& mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();

                if (mouseEvent->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    if (play.getBounds().contains(mousePos))
                    {            
                        if (!playMenuClick)
                        {
                            menuClickSound.play();
                            playMenuClick = true;
                        }

                        pendingReset = true;

                        gameState = gameState::level1Pause;
                    }

                    if (exit.getBounds().contains(mousePos))
                    {
                        if (!playMenuClick2)
                        {
                            menuClickSound.play();
                            playMenuClick2 = true;
                        }

                        window.close();
                    }

                    if (howToPlay.getBounds().contains(mousePos))
                    {
                        if (!playMenuClick3)
                        {
                            menuClickSound.play();
                            playMenuClick3 = true;
                        }

                        gameState = gameState::howtoPlay;
                    }

                    if (Menu.getBounds().contains(mousePos))
                    {
                        if (!playMenuClick4)
                        {
                            menuClickSound.play();
                            playMenuClick4 = true;
                        }

                        gameState = gameState::mainMenu;
                    }
                }
            }

        }

        if (pendingReset) 
        {
            enemies.clear();
            arrows.clear();
         
            knight.resetKnight();

            enemies.emplace_back(std::make_unique<Skeleton>(SkeletonIdle, SkeletonShot1, arrow, skeletonHurt, skeletonDead, 5560.f, 1825.f, 2));
            enemies.emplace_back(std::make_unique<wolf>(enemy, enemyAttack1, enemyAttack2, enemyAttack3, dead, wolfHurt, 3500.f, 2115.f));
            enemies.emplace_back(std::make_unique<wolf>(enemy, enemyAttack1, enemyAttack2, enemyAttack3, dead, wolfHurt, 2500.f, 1635.f));
            enemies.emplace_back(std::make_unique<Skeleton>(SkeletonIdle, SkeletonShot1, arrow, skeletonHurt, skeletonDead, 7892.f, 1060.f, 1));
            enemies.emplace_back(std::make_unique<wolf>(enemy, enemyAttack1, enemyAttack2, enemyAttack3, dead, wolfHurt, 7300.f, 1346.f));
            enemies.emplace_back(std::make_unique<wolf>(enemy, enemyAttack1, enemyAttack2, enemyAttack3, dead, wolfHurt, 7200.f, 100.f));
            enemies.emplace_back(std::make_unique<wolf>(enemy, enemyAttack1, enemyAttack2, enemyAttack3, dead, wolfHurt,  9000.f, 100.f));
            enemies.emplace_back(std::make_unique<Dragon>(dragonIdle, dragonWalk, dragonAttack2, dragonRise, dragonFlight, dragonSpecial, dragonLanding, dragonHurt, dragonDead, fontText, 14000.f, 100.f));
           
            pendingReset = false;
        }

        switch (gameState)
        {
        case gameState::mainMenu:

            if (playSong)
            {
                menuMusic.play();
                knight.music.stop();
                for (auto& enemy : enemies) {
                    Dragon* dragon = dynamic_cast<Dragon*>(enemy.get());
                    if (dragon)
                    {
                        dragon->bossMusic.stop();
                        dragon->dragonFlapSound.stop();
                        dragon->dragonFlameSound.stop();  
                        dragon->dragonFireSpecialSound.stop();
                        dragon->bossMusic.setVolume(100.f);
                    }
                }

                levelDelay.reset();
                deathDelay.reset();
                backToMenuDelay.reset();
                endDelayToMenu.reset();
                endDelay.reset();
                alpha = 0.f;
                playSong3 = true;
                playSong2 = true;
                playSong = false;
                playSong4 = true;
                window.setMouseCursorVisible(true);
            }

            playMenuClick = false;
            playMenuClick2 = false;
            playMenuClick3 = false;
            playMenuClick4 = false;


            window.setView(defaultView);

            //MOVING BACKGROUND
            ///////////////////////////////////////////////////////////////////////////////////
            img1.move({ -bgSpeed * deltaTime, 0.f });
            img2.move({ -bgSpeed * deltaTime, 0.f });

            //  Reset when one sprite goes off-screen
            if (img1.getPosition().x + titleBackground.getSize().x < 0)
                img1.setPosition({ img2.getPosition().x + titleBackground.getSize().x, 0.f });

            if (img2.getPosition().x + titleBackground.getSize().x < 0)
                img2.setPosition({ img1.getPosition().x + titleBackground.getSize().x, 0.f });
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////

            window.draw(img1);
            window.draw(img2);
            window.draw(banner);
            window.draw(banner2);
            window.draw(banner3);
            window.draw(banner4);
            window.draw(banner5);
            window.draw(banner6);
           window.draw(banner7);

            play.draw(window);
            exit.draw(window);
            title.draw(window);
            howToPlay.draw(window);

            if (play.getBounds().contains(mousePos))
            {
                play.getText().setFillColor(sf::Color::Yellow); // Highlight

                if (!playMenuSound)
                {
                    menuSelectSound.play();
                    playMenuSound = true;
                }
            }
            else
            {
                play.getText().setFillColor(sf::Color::White); // Normal
                playMenuSound = false;
            }

            if (exit.getBounds().contains(mousePos))
            {
                exit.getText().setFillColor(sf::Color::Yellow); // Highlight

                if (!playMenuSound2)
                {
                    menuSelectSound.play();
                    playMenuSound2 = true;
                }
            }
            else
            {
                exit.getText().setFillColor(sf::Color::White); // Normal
                playMenuSound2 = false;
            }

            if (howToPlay.getBounds().contains(mousePos))
            {
                howToPlay.getText().setFillColor(sf::Color::Yellow); // Highlight

                if (!playMenuSound3)
                {
                    menuSelectSound.play();
                    playMenuSound3 = true;
                }
            }
            else
            {
                howToPlay.getText().setFillColor(sf::Color::White); // Normal

                playMenuSound3 = false;
            }

            break;

        case gameState::playing:
        {
           
            if (playSong2)
            {
                knight.music.setVolume(100.f);
                knight.music.play();
                menuMusic.stop();
                playSong = true;
                playSong2 = false;
                window.setMouseCursorVisible(false);

            }

            window.draw(backgroundShape);
            for (auto& tile : tiles) {
                tile.draw(window);

            }

            knight.draw(window, tiles);         

            for (auto& enemy : enemies)
            {
                enemy->draw(window);
            }

            for (const auto& arrow2 : arrows)
            {
                window.draw(arrow2.sprite);

            }

            window.draw(inventory);
            window.draw(knight.healthPotion);

            knight.potionNumText.draw(window);

            knight.update(deltaTime, tiles, enemies, arrows);
           

            if (knight.Death())
            {
                deathDelay.start();

                if (deathDelay.getElapsedTime() > deathTime)
                {
                    gameState = gameState::paused;
                }


            }
          
            for (auto it = arrows.begin(); it != arrows.end(); )
            {
                it->update(deltaTime, arrows, tiles);
                
                for (const auto& tile : tiles)
                {
                    if (tile.isCollidableTile() && it->getBounds().findIntersection(tile.getBounds()))
                    {
                        it->velocity = { 0.f, 0.f };
                        it->setArrowOnTile(true); 
                    }
                }

                if (it->isExpired())
                    it = arrows.erase(it);
                else
                    ++it;
            }

            for (auto& enemy : enemies)
            {
                Skeleton* skeleton = dynamic_cast<Skeleton*>(enemy.get());
                if (skeleton)
                {
                    if (!enemy->isDead())
                        skeleton->shootArrow(arrows, tiles, deltaTime); // Shoots arrow if needed
                }


                enemy->update(deltaTime, tiles, enemies);

            }


            sf::Vector2f knightPosition = knight.getKnightBox().getPosition();

            // Get current camera center
            sf::Vector2f center = view.getCenter();
            sf::Vector2f target = center; // Start with current center

            if (knightPosition.x > center.x + margin) {
                target.x = knightPosition.x - knightOffset;
            }
            // Knight moves left beyond margin
            else if (knightPosition.x < center.x - margin) {
                target.x = knightPosition.x + knightOffset;
            }

          
            float halfWindowWidth = windowWidth / 2.f;
            if (target.x < halfWindowWidth)
                target.x = halfWindowWidth;
            if (target.x > worldWidth - halfWindowWidth)
                target.x = worldWidth - halfWindowWidth;

            // Smoothly move the current center toward the target
            center.x += (target.x - center.x) * lerpSpeed * deltaTime;


            float marginY = 100.f; // vertical margin buffer

            if (knight.getKnightBox().getGlobalBounds().position.y < 2000)
            {

                if (knightPosition.y > center.y + marginY) {
                    center.y = knightPosition.y - marginY;
                }
                else if (knightPosition.y < center.y - marginY) {
                    center.y = knightPosition.y + marginY;
                }

            }

            center.x = std::floor(center.x + 0.5f);
            center.y = std::floor(center.y + 0.5f);

            view.setCenter(center);
            window.setView(view);

            // Parallax background offset 
            int textureWidth = background.getSize().x;
            float parallaxFactor = 0.1f;

            int offsetX = static_cast<int>(center.x * parallaxFactor) % textureWidth;
            backgroundShape.setTextureRect(sf::IntRect({ offsetX, 0 }, { windowWidth, windowHeight }));
            backgroundShape.setPosition({ center.x - windowWidth / 2.f, center.y - windowHeight / 2.f });

            for (auto& enemy : enemies) {
                Dragon* dragon = dynamic_cast<Dragon*>(enemy.get());
                if (dragon)
                {
                    dragon->setBackgroundShape(&backgroundShape);

                    if (dragon->isDead())
                    {
                        endDelay.start();

                        dragon->bossMusic.setVolume(30.f);

                        if (endDelay.getElapsedTime() > endTime)
                        {
                            gameState = gameState::end;
                        }

                       
                    }
                }

            }
           
            healthBar.update(deltaTime, knight.getHealth(), 100.f, backgroundShape.getPosition().x + 50, backgroundShape.getPosition().y + 30);
            knight.healthText.setPosition(backgroundShape.getPosition().x + 15, backgroundShape.getPosition().y);
            heartSprite.setPosition({ backgroundShape.getPosition().x + 15, backgroundShape.getPosition().y + 8 });
            knight.healthPotion.setPosition({ backgroundShape.getPosition().x + 15, backgroundShape.getPosition().y + 900});
            knight.potionNumText.setPosition( backgroundShape.getPosition().x + 100, backgroundShape.getPosition().y + 975 );

            inventory.setPosition({ backgroundShape.getPosition().x + 20, backgroundShape.getPosition().y + 850 });

            healthBar.draw(window);
            window.draw(heartSprite);
           
            break;
        }
        case gameState::paused:


            if (playSong3)
            {
                knight.deathMusic.play();
                playSong3 = false;
            }
            knight.music.setVolume(30.f);


            window.draw(backgroundShape);
            for (auto& tile : tiles) {
                tile.draw(window);

            }

            knight.draw(window, tiles);

            for (auto& enemy : enemies)
            {
                enemy->draw(window);
            }

            for (const auto& arrow2 : arrows)
            {
                window.draw(arrow2.sprite);

            }


            outline = knight.deathText.getText().getOutlineColor();
            outline.a = static_cast<unsigned char>(alpha);
            knight.deathText.getText().setOutlineColor(outline);

            alpha += fadeSpeed * deltaTime;
            if (alpha > 255.f) alpha = 255.f;
            t = alpha / 255.f;
            eased = t * t;        
            c.a = static_cast<unsigned char>(255.f * eased);
            knight.deathText.getText().setFillColor(c);

            knight.deathText.setPosition(backgroundShape.getPosition().x + 500, backgroundShape.getPosition().y + 300);
            knight.deathText.draw(window);


            backToMenuDelay.start();
            if (backToMenuDelay.getElapsedTime() > backToMenuTime)
            {
                gameState = gameState::mainMenu;
            }
        

            break;

        case gameState::level1Pause:
            
            levelOne.draw(window);
            menuMusic.stop();
            levelDelay.start();
            window.setMouseCursorVisible(false);
          
            if (levelDelay.getElapsedTime() > levelTime)
            {
                gameState = gameState::playing;
            }


           break;

        case gameState::end:

            if (playSong4)
            {
                knight.enemeyFelledSound.play();
                playSong4 = false;
            }
            window.draw(backgroundShape);
            for (auto& tile : tiles) {
                tile.draw(window);

            }

            knight.draw(window, tiles);

            for (auto& enemy : enemies)
            {
                enemy->draw(window);
            }

            for (const auto& arrow2 : arrows)
            {
                window.draw(arrow2.sprite);

            }

            outline = knight.ending.getText().getOutlineColor();
            outline.a = static_cast<unsigned char>(alpha);
            knight.ending.getText().setOutlineColor(outline);

            alpha += fadeSpeed * deltaTime;
            if (alpha > 255.f) alpha = 255.f;
            t = alpha / 255.f;
            eased = t * t;
            c2.a = static_cast<unsigned char>(255.f * eased);
            knight.ending.getText().setFillColor(c2);

            knight.ending.setPosition(backgroundShape.getPosition().x + 300, backgroundShape.getPosition().y + 300);
            knight.ending.draw(window);

            endDelayToMenu.start();

            if (endDelayToMenu.getElapsedTime() > endTimeToMenu)
            {
                gameState = gameState::mainMenu;
            }

            break;

        case gameState::howtoPlay:

            if (Menu.getBounds().contains(mousePos))
            {
                Menu.getText().setFillColor(sf::Color::Yellow); // Highlight

                if (!playMenuSound4)
                {
                    menuSelectSound.play();
                    playMenuSound4 = true;
                }
            }
            else
            {
                Menu.getText().setFillColor(sf::Color::White); // Normal

                playMenuSound4 = false;
            }

            window.draw(forestBackgroundShape);
            rules.draw(window);
            rules2.draw(window);
            howToPlay2.draw(window);
            Menu.draw(window);
          
            knightWalkDemo.update(deltaTime);
            knightWalkDemo.setPosition( 200,200 );

            knightJumpDemo.update(deltaTime);
            knightJumpDemo.setPosition(630, 200);

            knightSprintDemo.update(deltaTime);
            knightSprintDemo.setPosition(1160, 200);

            knightAttackDemo.update(deltaTime);
            knightAttackDemo.setPosition(1600, 200);

            knightGuardDemo.update(deltaTime);
            knightGuardDemo.setPosition(200, 600);

            knightRollingDemo.update(deltaTime);
            knightRollingDemo.setPosition(560, 600);

            knightHangingDemo.update(deltaTime);
            knightHangingDemo.setPosition(950, 600);

            knightDrinkingDemo.update(deltaTime);
            knightDrinkingDemo.setPosition(1350, 600);

            tileSprite.setPosition({ 1010.f, 600.f });

            window.draw(tileSprite);
            window.draw(knightWalkDemo.getSprite());
            window.draw(knightJumpDemo.getSprite());
            window.draw(knightSprintDemo.getSprite());
            window.draw(knightAttackDemo.getSprite());
            window.draw(knightGuardDemo.getSprite());
            window.draw(knightRollingDemo.getSprite());
            window.draw(knightHangingDemo.getSprite());
            window.draw(knightDrinkingDemo.getSprite());
           

            break;
        
        }
               
       knight.drawCollisionBox(window);

        window.display();
    }
}