 #    Copyright (c) 2010-2016, Delft University of Technology
 #    All rigths reserved
 #
 #    This file is part of the Tudat. Redistribution and use in source and
 #    binary forms, with or without modification, are permitted exclusively
 #    under the terms of the Modified BSD license. You should have received
 #    a copy of the license with this file. If not, please or visit:
 #    http://tudat.tudelft.nl/LICENSE.
 #


# Set the source files.
set(PROPULSION_SOURCES
  "${SRCROOT}${PROPULSIONDIR}/thrustGuidance.cpp"
  "${SRCROOT}${PROPULSIONDIR}/thrustFunctions.cpp"
)

# Set the header files.
set(PROPULSION_HEADERS
  "${SRCROOT}${PROPULSIONDIR}/thrustAccelerationModel.h"
  "${SRCROOT}${PROPULSIONDIR}/thrustGuidance.h"
  "${SRCROOT}${PROPULSIONDIR}/thrustFunctions.h"
  "${SRCROOT}${PROPULSIONDIR}/thrustMagnitudeWrapper.h"
  "${SRCROOT}${PROPULSIONDIR}/massRateFromThrust.h"
)

# Add static libraries.
add_library(tudat_propulsion STATIC ${PROPULSION_SOURCES} ${PROPULSION_HEADERS})
setup_tudat_library_target(tudat_propulsion "${SRCROOT}${PROPULSIONDIR}")

# Add unit tests.
set(PROPULSION_UNITTESTS
  "${SRCROOT}${PROPULSIONDIR}/UnitTests/unitTestBasicAstrodynamics.cpp"
  "${SRCROOT}${PROPULSIONDIR}/UnitTests/unitTestAstrodynamicsFunctions.cpp"
  "${SRCROOT}${PROPULSIONDIR}/UnitTests/unitTestOrbitalElementConversions.cpp"
  "${SRCROOT}${PROPULSIONDIR}/UnitTests/unitTestPhysicalConstants.cpp"
  "${SRCROOT}${PROPULSIONDIR}/UnitTests/unitTestUnitConversions.cpp"
  "${SRCROOT}${PROPULSIONDIR}/UnitTests/unitTestUnifiedStateModelElementConversions.cpp"
)

add_executable(test_ThrustAcceleration "${SRCROOT}${PROPULSIONDIR}/UnitTests/unitTestThrustAcceleration.cpp")
setup_custom_test_program(test_ThrustAcceleration "${SRCROOT}${PROPULSIONDIR}")
target_link_libraries(test_ThrustAcceleration ${TUDAT_PROPAGATION_LIBRARIES} ${Boost_LIBRARIES})
