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

#ifndef CPPMICROSERVICES_SERVLETCONTEXT_H
#define CPPMICROSERVICES_SERVLETCONTEXT_H

#include "cppmicroservices/GlobalConfig.h"
#include "cppmicroservices/httpservice/HttpServiceExport.h"
#include "cppmicroservices/httpservice/IServletContext.h"

#include <memory>
#include <string>

namespace cppmicroservices {

class ServletContainer;

class US_HttpService_EXPORT ServletContext : public IServletContext
{
public:
  std::string GetContextPath() const override;

  std::shared_ptr<IServletContext> GetContext(
    const std::string& uripath) override;

  std::string GetMimeType(const std::string& file) const override;

private:
  friend struct ServletContainerPrivate;
  friend class HttpServiceFactory;

  ServletContext(ServletContainer* container);
  ServletContainer* m_Container;
};
}

#endif // CPPMICROSERVICES_SERVLETCONTEXT_H
