/*    Copyright (c) 2010-2015, Delft University of Technology
 *    All rights reserved.
 *
 *    Redistribution and use in source and binary forms, with or without modification, are
 *    permitted provided that the following conditions are met:
 *      - Redistributions of source code must retain the above copyright notice, this list of
 *        conditions and the following disclaimer.
 *      - Redistributions in binary form must reproduce the above copyright notice, this list of
 *        conditions and the following disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *      - Neither the name of the Delft University of Technology nor the names of its contributors
 *        may be used to endorse or promote products derived from this software without specific
 *        prior written permission.
 *
 *    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
 *    OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *    COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 *    GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *    AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 *    OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *    Changelog
 *      YYMMDD    Author            Comment
 *      150501    D. Dirkx          Ported from personal code
 *
 *    References
 *
 *    Notes
 *
 */

#include "Tudat/Astrodynamics/BasicAstrodynamics/accelerationModelTypes.h"

namespace tudat
{

namespace basic_astrodynamics
{

//! Function to get a string representing a 'named identification' of an acceleration type
std::string getAccelerationModelName( const AvailableAcceleration accelerationType )
{
    std::string accelerationName;
    switch( accelerationType )
    {
    case central_gravity:
        accelerationName = "central gravity ";
        break;
    case aerodynamic:
        accelerationName = "aerodynamic ";
        break;
    case cannon_ball_radiation_pressure:
        accelerationName = "cannonball radiation pressure ";
        break;
    case spherical_harmonic_gravity:
        accelerationName = "spherical harmonic gravity ";
        break;
    case mutual_spherical_harmonic_gravity:
        accelerationName = "mutual spherical harmonic gravity ";
        break;
    case third_body_central_gravity:
        accelerationName = "third-body central gravity ";
        break;
    case third_body_spherical_harmonic_gravity:
        accelerationName = "third-body spherical harmonic gravity ";
        break;
    case third_body_mutual_spherical_harmonic_gravity:
        accelerationName = "third-body mutual spherical harmonic gravity ";
        break;
    case thrust_acceleration:
        accelerationName = "thrust ";
        break;
    default:
        std::string errorMessage = "Error, acceleration type " +
                boost::lexical_cast< std::string >( accelerationType ) +
                "not found when retrieving acceleration name ";
        throw std::runtime_error( errorMessage );
    }
    return accelerationName;
}

//! Function to identify the derived class type of an acceleration model.
AvailableAcceleration getAccelerationModelType(
        const boost::shared_ptr< basic_astrodynamics::AccelerationModel< Eigen::Vector3d > >
        accelerationModel )
{
    using namespace tudat::aerodynamics;
    using namespace tudat::electro_magnetism;
    using namespace tudat::gravitation;

    // Nominal type is undefined
    AvailableAcceleration accelerationType = undefined_acceleration;

    // Check for each accelerarion mdoel type implemented as AvailableAcceleration.
    if( boost::dynamic_pointer_cast< CentralGravitationalAccelerationModel3d >(
                accelerationModel ) != NULL )
    {
        accelerationType = central_gravity;
    }
    else if( boost::dynamic_pointer_cast< CannonBallRadiationPressureAcceleration >(
                 accelerationModel ) != NULL )
    {
        accelerationType = cannon_ball_radiation_pressure;
    }
    else if( boost::dynamic_pointer_cast< ThirdBodyCentralGravityAcceleration >(
                 accelerationModel ) != NULL )
    {
        accelerationType = third_body_central_gravity;
    }
    else if( boost::dynamic_pointer_cast< SphericalHarmonicsGravitationalAccelerationModel >(
                 accelerationModel ) != NULL  )
    {
        accelerationType = spherical_harmonic_gravity;
    }
    else if( boost::dynamic_pointer_cast< MutualSphericalHarmonicsGravitationalAccelerationModel >( accelerationModel ) != NULL )
    {
        accelerationType = mutual_spherical_harmonic_gravity;
    }
    else if( boost::dynamic_pointer_cast< AerodynamicAcceleration >(
                 accelerationModel ) != NULL )
    {
        accelerationType = aerodynamic;
    }
    else if( boost::dynamic_pointer_cast< propulsion::ThrustAcceleration >(
                 accelerationModel ) != NULL )
    {
        accelerationType = thrust_acceleration;
    }
    else
    {
        throw std::runtime_error(
                    "Error, acceleration model not identified when getting acceleration type." );
    }

    // Return identified type.
    return accelerationType;

}

//! Function to identify the type of a mass rate model.
AvailableMassRateModels getMassRateModelType(
        const boost::shared_ptr< MassRateModel > massRateModel )
{
    // Nominal type is undefined
    AvailableMassRateModels massRateType = undefined_mass_rate_model;

    // Check for each mass rate mdoel type implemented as AvailableMassRateModels.
    if( boost::dynamic_pointer_cast< basic_astrodynamics::CustomMassRateModel >(
                massRateModel ) != NULL )
    {
        massRateType = custom_mass_rate_model;
    }
    else if( boost::dynamic_pointer_cast< propulsion::FromThrustMassRateModel >(
                massRateModel ) != NULL )
    {
        massRateType = from_thrust_mass_rate_model;
    }
    else
    {
        throw std::runtime_error(
                    "Error, mass rate model not identified when getting mass rate model type." );
    }
    return massRateType;
}

//! Function to get all acceleration models of a given type from a list of models
std::vector< boost::shared_ptr< AccelerationModel3d > > getAccelerationModelsOfType(
        const std::vector< boost::shared_ptr< AccelerationModel3d > >& fullList,
        const AvailableAcceleration modelType )
{
    std::vector< boost::shared_ptr< AccelerationModel3d > > accelerationList;
    for( unsigned int i = 0; i < fullList.size( ); i++ )
    {
        if( getAccelerationModelType( fullList.at( i ) ) == modelType )
        {
            accelerationList.push_back( fullList.at( i  ) );
        }
    }
    return accelerationList;
}

} // namespace basic_astrodynamics

} // namespace tudat
