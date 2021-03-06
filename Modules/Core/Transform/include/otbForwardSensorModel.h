/*
 * Copyright (C) 2005-2017 Centre National d'Etudes Spatiales (CNES)
 *
 * This file is part of Orfeo Toolbox
 *
 *     https://www.orfeo-toolbox.org/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef otbForwardSensorModel_h
#define otbForwardSensorModel_h

#include "otbSensorModelBase.h"
#include "itkMacro.h"
#include "itkObject.h"

namespace otb
{

/** \class ForwardSensorModel

 * \brief Class for direct sensor models
 *
 * Based on ossimProjectionFactoryRegistry and ossimProjection methods.
 * It takes as input an index and computes the world coordinates.
 * (i, j, h) -> (lon, lat).
 * Notice that the elevation h is optional.
 *
 * \ingroup Transform
 * \ingroup Projection
 *
 * \ingroup OTBTransform
 */

template <class TScalarType,
    unsigned int NInputDimensions = 2,
    unsigned int NOutputDimensions = 2>
class ITK_EXPORT ForwardSensorModel : public SensorModelBase<TScalarType,
      NInputDimensions,
      NOutputDimensions>
{

public:
  /** Standard class typedefs. */
  typedef ForwardSensorModel Self;
  typedef SensorModelBase<TScalarType,
      NInputDimensions,
      NOutputDimensions>         Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  typedef typename Superclass::InputPointType  InputPointType;
  typedef typename Superclass::OutputPointType OutputPointType;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ForwardSensorModel, SensorModelBase);

  itkStaticConstMacro(InputSpaceDimension, unsigned int, NInputDimensions);
  itkStaticConstMacro(OutputSpaceDimension, unsigned int, NOutputDimensions);

  /** Compute the world coordinates. */
  OutputPointType TransformPoint(const InputPointType& point) const override;

protected:
  ForwardSensorModel();
  ~ForwardSensorModel() override;

  /** PrintSelf method */
  void PrintSelf(std::ostream& os, itk::Indent indent) const override;

private:

  ForwardSensorModel(const Self &); //purposely not implemented
  void operator =(const Self&);     //purposely not implemented

};

} // namespace otb

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbForwardSensorModel.txx"
#endif

#endif
