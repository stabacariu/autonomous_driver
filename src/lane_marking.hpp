/**
 * @file lane_marking.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 26.5.2017
 */
 
#ifndef LANE_MARKING_HPP
#define LANE_MARKING_HPP

enum LaneMarking {
    LANE_MARKING_NONE,
    LANE_MARKING_DASHED,
    LANE_MARKING_DASHED_SOLID,
    LANE_MARKING_SOLID
};

enum LaneMarkingType {
    LANE_MARKING_TYPE_NONE,
    LANE_MARKING_TYPE_SINGLE,
    LANE_MARKING_TYPE_DOUBLE
};

enum LaneMarkingPosition {
    LANE_MARKING_POSITION_NONE,
    LANE_MARKING_POSITION_GUIDE,
    LANE_MARKING_POSITION_EDGE
};

#endif // LANE_MAKRING_HPP
