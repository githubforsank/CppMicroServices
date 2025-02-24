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

#include "cppmicroservices/httpservice/HttpServiceFactory.h"

#include "HttpServletRequestPrivate.h"
#include "HttpServletResponsePrivate.h"

namespace cppmicroservices {

std::shared_ptr<HttpServletRequest>
HttpServiceFactory::CreateHttpServletRequest(
  std::shared_ptr<ServletContext> servletContext,
  CivetServer* server,
  mg_connection* conn)
{
  HttpServletRequestPrivate* p =
    new HttpServletRequestPrivate(servletContext, server, conn);
  auto request = std::make_shared<HttpServletRequest>(HttpServletRequest(p));
  return request;
}

std::shared_ptr<HttpServletResponse>
HttpServiceFactory::CreateHttpServletResponse(HttpServletRequest* request,
                                              CivetServer* server,
                                              mg_connection* conn)
{
  HttpServletResponsePrivate* p =
    new HttpServletResponsePrivate(request, server, conn);
  auto response = std::make_shared<HttpServletResponse>(HttpServletResponse(p));
  return response;
}

std::shared_ptr<ServletContext> HttpServiceFactory::CreateContext(
  ServletContainer* container)
{
  auto context = std::make_shared<ServletContext>(ServletContext(container));
  return context;
}
}
