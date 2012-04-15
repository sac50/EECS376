Header header

# laswer sweeps from the right(0) to left (180)

float32 boxWidth = 0.4 # HALVED. remember, robot teack is ~.56, so make this a little over half of that
float32 boxLength = 1.6

float32 leftClearance  # distance to ping furthest on our right (would be 180 if we checked all of them)
float32 rightClearance # distance to ping furthest on our right (would be 180 if we checked all of them)
float32 threatRange = 1.0 # Range inwhich if we've hit an object we need to consider replanning

float32 nearestObstacle
uint8 nearestTheta

float32 edgeDistance
uint8 edgeTheta

uint8 firstObstacleTheta ##should be rightmost obstacle ping
uint8 lastObstacleTheta

bool obstacle
