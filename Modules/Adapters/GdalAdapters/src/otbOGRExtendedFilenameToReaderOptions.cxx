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

#include "otbOGRExtendedFilenameToReaderOptions.h"

namespace otb
{

OGRExtendedFilenameToReaderOptions::
OGRExtendedFilenameToReaderOptions()
{
  m_Options.simpleFileName.first = false;
  m_Options.simpleFileName.second = "";

  m_Options.encoding.first = false;
  m_Options.encoding.second = "";

  m_Options.availableOptions.insert("encoding");
}

void
OGRExtendedFilenameToReaderOptions::
SetExtendedFileName(const char *extFname)
{
  Superclass::SetExtendedFileName(extFname);
  OptionMapType map = GetOptionMap();

  m_Options.simpleFileName.first  = true;
  m_Options.simpleFileName.second = this->GetSimpleFileName();


}


} //end namespace otb
