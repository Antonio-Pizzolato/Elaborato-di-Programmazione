#ifndef MAIN_CPP_LEVEL_H
#define MAIN_CPP_LEVEL_H

#include "../TextureManager.h"
#include "Torch.h"

// Constants for the game grid size.
static int const GRID_WIDTH = 19;
static int const GRID_HEIGHT = 19;
// Room count for procedurally generated level.
static int const ROOMS_COUNT = 50;
// Torches count per generated level.
static int const TORCHES_COUNT = 10;
// The width and height of each tile in pixels.
static int const TILE_SIZE = 50;

struct Tile {
    TILE type{};
    int columnIndex{};                    // The column index of the tile.
    int rowIndex{};                        // The row index of the tile.
    sf::Sprite sprite;                    // The tile sprite.
    int H{};                                // Heuristic / movement cost to goal.
    int G{};                                // Movement cost. (Total of entire path)
    int F{};                                // Estimated cost for full path. (G + H)
    Tile *parentNode{};
};

class Level {
public:
    Level();
    /**
     * Constructor.
     * A renderWindow is needed in order for the level to calculate its position.
     * @param window The game window.
     */
    explicit Level(sf::RenderWindow &window);

    /**
     * Returns true if the given tile index is solid.
     * @param columnIndex The tile's column index.
     * @param rowIndex The tile's row index.
     * @return True if the given tile is solid.
     */
    bool IsSolid(int columnIndex, int rowIndex);
    /**
     * Sets the index of a given tile in the 2D game grid.
     * This also changes the tile sprite, and is how tiles should be changed and set manually.
     * @param columnIndex The tile's column index.
     * @param rowIndex The tile's row index.
     * @param index The new index of the tile.
     */
    void SetTile(int columnIndex, int rowIndex, TILE tileType);
    /**
     * Draws the level grid to the provided render window.
     * @param window The render window to draw the level to.
     * @param timeDelta The time that has elapsed since the last update.
     */
    void Draw(sf::RenderWindow &window, float dt);
    /**
     * Gets the tile at the given position.
     * @param position The coordinates of the position to check.
     * @return A pointer to the tile at the given location.
     */
    Tile *GetTile(sf::Vector2f position);
    /**
    * Gets the tile at the given position in the level array.
    * @param columnIndex The column that the tile is in.
    * @param rowIndex The row that the tile is in.
    * @return A pointer to the tile if valid.
    */
    Tile *GetTile(int columnIndex, int rowIndex);
    /**
     * Checks if a given tile is valid.
     * @param columnIndex The column that the tile is in.
     * @param rowIndex The column that the row is in.
     * @return True if the tile is valid.
     */
    static bool TileIsValid(int columnIndex, int rowIndex);
    /**
     * Gets the current floor number.
     * @return The current floor.
     */
    int GetFloorNumber() const;
    /**
     * Gets the current room number.
     * @return The current room.
     */
    int GetRoomNumber() const;
    /**
     * Gets the size of the level in terms of tiles.
     * @return The size of the level grid.
     */
    static sf::Vector2i GetSize();
    /**
     * Unlocks the door in the level.
     */
    void UnlockDoor();
    /**
     * Return true if the given tile is a floor tile.
     * @param columnIndex The column that the tile is in.
     * @param rowIndex The column that the row is in.
     * @return True if the given tile is a floor tile.
     */
    bool IsFloor(int columnIndex, int rowIndex);
    /**
    * Return true if the given tile is a floor tile.
    * @param tile The tile to check
    * @return True if the given tile is a floor tile.
    */
    static bool IsFloor(const Tile &tile);
    /**
    * Adds a tile to the level.
    * These tiles are essentially sprites with a unique index. Once added, they can be loaded via the LoadLevelFromFile() function by including its index in the level data.
    * @param fileName The path to the sprite resource, relative to the project directory.
    * @param tileType The type of tile that is being added.
    * @return The index of the tile. This is used when building levels.
    */
    int AddTile(const std::string &fileName, TILE tileType);
    /**
     * Get an absolute location for a tile.
     * @param columnIndex The column that the tile is in.
	 * @param rowIndex The row that the tile is in.
     * @return Vector with `x` and `y` attributes.
     */
    sf::Vector2f GetActualTileLocation(int columnIndex, int rowIndex) const;
    /**
     * Get a vector with locations for all existing floor tiles on the level.
     * @return Vector with locations for all existing floor tiles.
     */
    std::vector<sf::Vector2f> GetFloorLocations();
    /**
     * Get random reachable location
     * @return Returns a valid spawn location from the currently loaded level.
     */
    sf::Vector2f GetRandomSpawnLocation();
    /**
     * Sets the overlay color of the level tiles.
     * @param tileColor The new tile overlay color
     */
    void SetColor(sf::Color tileColor);
    /**
     * Resets the A* data of all level tiles.
     */
    void ResetNodes();
    /**
     * Generates a random level.
     */
    void GenerateLevel();
    /**
     * Calculates the correct texture for each tile in the level.
     */
    void CalculateTextures();
    /**
     * Set a random color for the generated level;
     */
    void SetRandomColor();
    /**
     * Generates an entry and exit point for the given level.
     */
    void GenerateEntryAndExit();
    /**
     * Returns the spawn location for the current level.
     */
    sf::Vector2f SpawnLocation();
    /**
     * Generates an torches for the given level.
     */
    void GenerateTorches();
private:
    /**
     * Checks if a given tile is a wall block.
     * @param columnIndex The column that the tile is in.
     * @param rowIndex The column that the row is in.
     * @return True if the given tile is a wall tile.
     */
    bool IsWall(int columnIndex, int rowIndex);
    /**
     * Creates a path between two nodes in the recursive backtracker algorithm.
     */
    void CreatePath(int columnIndex, int rowIndex);
    /**
     * Adds a given number of randomly sized rooms to the level to create some open space.
     */
    void CreateRooms(int roomCount);
private:
    /**
     * A 2D array that describes the level data.
     * The type is Tile, which holds a sprite and an index.
     */
    Tile grid[GRID_WIDTH][GRID_HEIGHT];
    /**
     *  A vector with locations of all reachable tiles on the map.
     *  Internally used for random objects spawning.
     */
    std::vector<sf::Vector2f> reachableTiles;
    /**
     * The position of the level relative to the window.
     * This is to the top-left of the level grid.
     */
    sf::Vector2i origin;
    /**
    * The floor number that the player is currently on.
    */
    int floorNumber{};
    /**
    * The room number that the player is currently in.
    */
    int roomNumber{};
    /**
     * An array containing all texture IDs of the level tiles.
     */
    int textureIDs[static_cast<int>(TILE::COUNT)]{};
    /**
     * The indices of the tile containing the levels door.
     */
    sf::Vector2i doorTileIndices;
    /**
     * A vector of all tiles in the level.
     */
    std::vector<std::shared_ptr<Torch>> torches;
    /**
     * The spawn location for the current level.
     */
    sf::Vector2f spawnLocation;
};

#endif //MAIN_CPP_LEVEL_H
