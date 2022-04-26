##### Done:
- [x] Create camera 
- [x] Create global coordinate system in Cartesian
- [x] Draw mini map (on B button press)
- [x] Draw isometric tiles

##### To do:
- [ ] Add roads
- [ ] Looping map?
- [ ] Optimize draw functions to only render onscreen tiles?
- [ ] Building class/states?
- [ ] Add player
- [ ] Add fire
- [ ] Add police
- [ ] Add firefighters (or add their behaviors to police to save space)?

//Changes to make:
- [ ] Create pause function on B button press (using deltatime) and call drawMap function in it or don't pause on button press and sync up isometric and Cartesian coordinates in both maps
- [ ] Add blank tile to tile sprites

### General layout (rough outline)

#### Gamestates:

**[Menu state]**

**[Pause state?]**

**[Game state]**
- Populate map with buildings and blank tiles
- Populate map with roads
- Extend enum to include other tile states?
    - Walkable/not walkable
    - Building complete, burning (maybe not burning, see below function*), destroyed.
- Draw map

- Create player (x and y position, health)
- Add player movement and animations
- Draw player

- Create police class (x and y position, movement, behavior)
    - Check neighboring tile states if walkable
    - Check neighboring tiles for player
    If player is found, follow player (make movement slightly slower than player?)
- Create instances of police class
- Draw police

*Check neighboring building states and everyXframes to determine fire propagation:

if(arduboy.everyXFrames(15)) {
    if(isOnFire(building[y][x])) {
        auto & neighbour = building[y - 1][x];
        if(!isOnFire(neighbour) && isDestroyed(neighbour)) {
            setOnFire(neighbour);   
        }
    }
}