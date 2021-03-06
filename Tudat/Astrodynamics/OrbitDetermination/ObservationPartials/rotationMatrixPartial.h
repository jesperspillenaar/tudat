/*    Copyright (c) 2010-2016, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#ifndef TUDAT_ROTATIONMATRIXPARTIAL_H
#define TUDAT_ROTATIONMATRIXPARTIAL_H

#include <vector>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/assign/list_of.hpp>

#include <Eigen/Core>

#include "Tudat/Astrodynamics/Ephemerides/simpleRotationalEphemeris.h"
#include "Tudat/Astrodynamics/OrbitDetermination/EstimatableParameters/estimatableParameter.h"

namespace tudat
{

namespace observation_partials
{

//! Function to calculate a rotation matrix from a body-fixed to inertial frame w.r.t. a constant rotation rate.
/*!
 * Function to calculate a rotation matrix from a body-fixed to inertial frame, as computed by the SimpleRotationalEphemeris
 * class,  w.r.t. the constant rotation rate.
 * \param inertialBodyFixedToIntegrationFrame Rotation matrix at reference epoch
 * \param rotationRate Nominal rotation rate (about local z-axis)
 * \param timeSinceEpoch Elapsed time (in seconds) since reference epoch
 * \return Partial derivative of rotation matrix w.r.t. rotation rate.
 */
Eigen::Matrix3d calculatePartialOfRotationMatrixFromLocalFrameWrtConstantRotationRate(
        const Eigen::Quaterniond inertialBodyFixedToIntegrationFrame,
        const double rotationRate, const double timeSinceEpoch );

//! Function to calculate a rotation matrix from a body-fixed to inertial frame w.r.t. a constant pole right ascension
//! and declination.
/*!
 * Function to calculate a rotation matrix from a body-fixed to inertial frame, as computed by the SimpleRotationalEphemeris
 * class,  w.r.t. a constant pole right ascension and declination.
 * \param initialOrientationAngles Rotation Euler angles at reference epoch, in order right ascension, declination,
 * prime meridian
 * \param rotationRate Rotation rate (about local z-axis)
 * \param timeSinceEpoch Elapsed time (in seconds) since reference epoch
 * \return Partial derivatives of rotation matrix w.r.t. right ascension (entry 0) and declination (entry 1) of pole.
 */
std::vector< Eigen::Matrix3d > calculatePartialOfRotationMatrixFromLocalFrameWrtPoleOrientation(
        const Eigen::Vector3d initialOrientationAngles,
        const double rotationRate, const double timeSinceEpoch );

//! Base class for partial derivatives of rotation matrix from body fixed to inertial frame w.r.t. a parameter.
/*!
 *  Base class for partial derivatives of rotation matrix from body fixed to inertial frame w.r.t. a parameter.
 *  A derived class is implemented for each estimatable parameter which represents a property of a rotation matrix from a
 *  body-fixed frame (as defined by the isParameterRotationMatrixProperty function). Pointers to this class are used for
 *  both PositionPartials and the SphericalHarmonicsGravityPartial partial. In this manner, only a single partial object
 *  needs to be implemented for both the position and partial and the sh acceleration
 *  partial wrt a rotational parameter when such a parameter is added.
 */
class RotationMatrixPartial
{
public:

    //! Virtual destructor
    virtual ~RotationMatrixPartial( ){ }

    //! Function to calculate partials of rotation matrix wrt a parameter (for either double or VectorXd parameters).
    /*!
     *  Function to calculate partials of rotation matrix from the body-fixed to the inertial base frame wrt a parameter.
     *  For a double parameter, the size of the return vector is 1, for a VectorXd parameter, the size is equal to the size
     *  of the parameter and the entries of the vector returned from here correspond to partials of the same index in the
     *  parameter.
     *  \param time Time at which the partial(s) is(are) to be evaluated.
     *  \return Vector of partials of rotation matrix from body-fixed to inertial frame wrt parameter(s)
     */
    virtual std::vector< Eigen::Matrix3d > calculatePartialOfRotationMatrixToBaseFrameWrParameter(
            const double time ) = 0;

    //! Function to calculate the partial of the position of a vector, which is given in a body-fixed frame, in the inertial
    //! frame wrt a parameter.
    /*!
     *  Function to calculate the partial of the position of a vector, which is given in a body-fixed frame, in the inertial
     *  frame wrt a parameter  denoting a property of the rotation between a body-fixed and an inertial frame. The type of
     *  parameter is defined by the derived class and a a separate derived class is impleneted for each parameter.
     *  An example is the change in position of a ground station,  as expressed in the inertial frame, wrt a rotational
     *  parameter. Each column of the return Matrix denotes a single entry of the parameter
     *  (so it is a Vector3d for a double parameter).
     *  \param time Time at which the partial is to be evaluated.
     *  \param vectorInLocalFrame Vector, expressed in the body-fixed frame, of which the partial in an inertial frame wrt
     *  parameter is to be determined.
     *  \return Partial of the value of the vector in an inertial frame wrt the parameter(s).
     */
    Eigen::Matrix< double, 3, Eigen::Dynamic > calculatePartialOfRotatedVector(
            const double time,
            const Eigen::Vector3d vectorInLocalFrame );

    //! Function to return the secondary identifier of the estimated parameter
    /*!
     * Function to return the secondary identifier of the estimated parameter. This function returns an empty string by
     * default, and can be overridden in the derived class if the associated parameter has a secondary identifier.
     * \return  Secondary identifier of the estimated parameter
     */
    virtual std::string getSecondaryIdentifier( )
    {
        return "";
    }

};

//! Class to calculate a rotation matrix from a body-fixed to inertial frame w.r.t. a constant rotation rate.
/*!
 * Class to calculate a rotation matrix from a body-fixed to inertial frame, as computed by the SimpleRotationalEphemeris
 * class,  w.r.t. the constant rotation rate.
 */
class RotationMatrixPartialWrtConstantRotationRate: public RotationMatrixPartial
{
public:

    //! Constructor
    /*!
     * Constructor
     * \param bodyRotationModel Rotation model for which the partial derivative w.r.t. the rotation rate is to be taken.
     */
    RotationMatrixPartialWrtConstantRotationRate(
            const boost::shared_ptr< ephemerides::SimpleRotationalEphemeris > bodyRotationModel ):
        bodyRotationModel_( bodyRotationModel ){ }

    //! Destructor.
    ~RotationMatrixPartialWrtConstantRotationRate( ){ }

    //! Function to calculate partial of rotation matrix from the body-fixed to the inertial frame wrt a rotation rate.
    /*!
     *  Function to calculate partial of rotation matrix from the body-fixed to the inertial frame wrt a rotation rate,
     *  using the properties of the bodyRotationModel_ member.
     *  \param time Time at which the partial is to be evaluated.
     *  \return Vector of size 1 containing partials of rotation matrix from body-fixed to inertial frame wrt
     *  rotation rate.
     */
    std::vector< Eigen::Matrix3d > calculatePartialOfRotationMatrixToBaseFrameWrParameter(
            const double time )
    {
        return boost::assign::list_of(
                    calculatePartialOfRotationMatrixFromLocalFrameWrtConstantRotationRate(
                        bodyRotationModel_->getInitialRotationToTargetFrame( ).inverse( ),
                        bodyRotationModel_->getRotationRate( ),
                        time - bodyRotationModel_->getInitialSecondsSinceEpoch( ) ) );
    }
private:

    //! Rotation model for which the partial derivative w.r.t. the rotation rate is to be taken.
    boost::shared_ptr< ephemerides::SimpleRotationalEphemeris > bodyRotationModel_;
};

//! Class to calculate a rotation matrix from a body-fixed to inertial frame w.r.t. a constant pole right ascension
//! and declination
/*!
 * Class to calculate a rotation matrix from a body-fixed to inertial frame, as computed by the SimpleRotationalEphemeris
 * class,  w.r.t. the constant pole right ascension and declination
 */
class RotationMatrixPartialWrtPoleOrientation: public RotationMatrixPartial
{
public:

    //! Constructor
    /*!
     * Constructor
     * \param bodyRotationModel Rotation model for which the partial derivative w.r.t. the pole position is to be taken.
     */
    RotationMatrixPartialWrtPoleOrientation(
            const boost::shared_ptr< ephemerides::SimpleRotationalEphemeris > bodyRotationModel ):
        bodyRotationModel_( bodyRotationModel ){ }

    //! Destructor.
    ~RotationMatrixPartialWrtPoleOrientation( ){ }

    //! Function to calculate partial of rotation matrix from the body-fixed to the inertial frame wrt pole
    //! right ascension and declination.
    /*!
     *  Function to calculate partial of rotation matrix from the body-fixed to the inertial frame  wrt pole
     *  right ascension and declination, using the properties of the bodyRotationModel_ member.
     *  \param time Time at which the partial is to be evaluated.
     *  \return Vector of size 2 containing partials of rotation matrix from body-fixed to inertial frame right ascension
     *  (entry 0) and declination (entry 1) of pole.
     */
    std::vector< Eigen::Matrix3d > calculatePartialOfRotationMatrixToBaseFrameWrParameter(
            const double time )
    {
        return calculatePartialOfRotationMatrixFromLocalFrameWrtPoleOrientation(
                    bodyRotationModel_->getInitialEulerAngles( ),
                    bodyRotationModel_->getRotationRate( ), time - bodyRotationModel_->getInitialSecondsSinceEpoch( ) );
    }

private:

    //! Rotation model for which the partial derivative w.r.t. the rotation rate is to be taken.
    boost::shared_ptr< ephemerides::SimpleRotationalEphemeris > bodyRotationModel_;
};


//! Typedef of list of RotationMatrixPartial objects, ordered by parameter.
typedef std::map< std::pair< estimatable_parameters::EstimatebleParametersEnum, std::string >,
boost::shared_ptr< observation_partials::RotationMatrixPartial > > RotationMatrixPartialNamedList;


} // namespace observation_partials

} // namespace tudat

#endif // TUDAT_ROTATIONMATRIXPARTIAL_H
