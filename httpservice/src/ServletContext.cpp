/*=============================================================================

  Library: CppMicroServices

  Copyright (c) The CppMicroServices developers. See the COPYRIGHT
  file at the top-level directory of this distribution and at
  https://github.com/CppMicroServices/CppMicroServices/COPYRIGHT .

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/

#include "cppmicroservices/httpservice/ServletContext.h"
#include "ServletContainerPrivate.h"
#include "cppmicroservices/httpservice/ServletContainer.h"

namespace cppmicroservices {

ServletContext::ServletContext(ServletContainer* container)
  : m_Container(container)
{}

std::string ServletContext::GetContextPath() const
{
  return m_Container->GetContextPath(this);
}

std::shared_ptr<IServletContext> ServletContext::GetContext(
  const std::string& uripath)
{
  return m_Container->GetContext(uripath);
}

std::string ServletContext::GetMimeType(const std::string& file) const
{
  return m_Container->d->GetMimeType(this, file);
}
}
