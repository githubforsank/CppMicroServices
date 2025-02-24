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

#ifndef CPPMICROSERVICES_HTTPSERVICEFACTORY_H
#define CPPMICROSERVICES_HTTPSERVICEFACTORY_H

#include "cppmicroservices/httpservice/HttpServletRequest.h"
#include "cppmicroservices/httpservice/HttpServletResponse.h"
#include "cppmicroservices/httpservice/ServletContainer.h"
#include "cppmicroservices/httpservice/ServletContext.h"

#include <civetweb/CivetServer.h>
#include <civetweb/civetweb.h>

#include <memory>

namespace cppmicroservices {
class US_HttpService_EXPORT HttpServiceFactory
{

public:
  /*!
  * Create an instance of HttpServletRequest, where Civet server and connection may be null.
  */
  static std::shared_ptr<HttpServletRequest> CreateHttpServletRequest(
    std::shared_ptr<ServletContext> servletContext,
    CivetServer* server,
    mg_connection* conn);

  /*!
  * Create an instance of HttpServletRequest, where Civet server and connection may be null.
  */
  static std::shared_ptr<HttpServletResponse> CreateHttpServletResponse(
    HttpServletRequest* request,
    CivetServer* server,
    mg_connection* conn);

  /*!
  * Create an empty servlet context
  */
  static std::shared_ptr<ServletContext> CreateContext(
    ServletContainer* container);
};
}
#endif
