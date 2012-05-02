/*    Copyright (c) 2010-2012 Delft University of Technology.
 *
 *    This software is protected by national and international copyright.
 *    Any unauthorized use, reproduction or modification is unlawful and
 *    will be prosecuted. Commercial and non-private application of the
 *    software in any form is strictly prohibited unless otherwise granted
 *    by the authors.
 *
 *    The code is provided without any warranty; without even the implied
 *    warranty of merchantibility or fitness for a particular purpose.
 *
 *    Changelog
 *      YYMMDD    Author            Comment
 *      110207    K. Kumar          First creation of code.
 *
 *    References
 *
 */

#ifndef TUDAT_CARTESIAN_VELOCITY_ELEMENTS_H
#define TUDAT_CARTESIAN_VELOCITY_ELEMENTS_H

#include <iostream>
#include "Tudat/Astrodynamics/States/state.h"

namespace tudat
{
namespace astrodynamics
{
namespace states
{

//! Cartesian position elements class.
/*!
 * This class contains the Cartesian position elements.
 */
class CartesianVelocityElements : public State
{
public:

    //! Default constructor.
    /*!
     * Default constructor.
     */
    CartesianVelocityElements( ) { state.setZero( 3 ); }

    //! Set Cartesian element: xDot.
    /*!
     * Sets the Cartesian element: xDot.
     * \param cartesianElementXDot Cartesian element: xDot.
     */
    void setCartesianElementXDot( const double cartesianElementXDot )
    {
        state( 0 ) = cartesianElementXDot;
    }

    //! Set Cartesian element: yDot.
    /*!
     * Sets the Cartesian element: yDot.
     * \param cartesianElementYDot Cartesian element: yDot.
     */
    void setCartesianElementYDot( const double cartesianElementYDot )
    {
        state( 1 ) = cartesianElementYDot;
    }

    //! Set Cartesian element: zDot.
    /*!
     * Sets the Cartesian element: zDot.
     * \param cartesianElementZDot Cartesian element: zDot.
     */
    void setCartesianElementZDot( const double cartesianElementZDot )
    {
        state( 2 ) = cartesianElementZDot;
    }

    //! Get Cartesian element: xDot.
    /*!
     * Returns the Cartesian element: xDot.
     * \return Cartesian element: xDot.
     */
    double getCartesianElementXDot( ) { return state( 0 ); }

    //! Get Cartesian element: yDot.
    /*!
     * Returns the Cartesian element: yDot.
     * \return Cartesian element: yDot.
     */
    double getCartesianElementYDot( ) { return state( 1 ); }

    //! Get Cartesian element: zDot.
    /*!
     * Returns the Cartesian element: zDot.
     * \return Cartesian element: zDot.
     */
    double getCartesianElementZDot( ) { return state( 2 ); }

    //! Overload ostream to print class information.
    /*!
     * Overloads ostream to print class information.
     * \param stream Stream object.
     * \param cartesianVelocityElements CartesianVelocityElements object.
     * \return Stream object.
     */
    friend std::ostream& operator<<( std::ostream& stream,
                                     CartesianVelocityElements& cartesianVelocityElements )
    {
        stream << "The state is set to: " << cartesianVelocityElements.state << std::endl;
        return stream;
    }

protected:

private:
};

} // namespace states
} // namespace astrodynamics
} // namespace tudat

#endif // TUDAT_CARTESIAN_VELOCITY_ELEMENTS_H