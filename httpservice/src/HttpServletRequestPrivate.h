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

#ifndef CPPMICROSERVICES_HTTPSERVLETREQUESTPRIVATE_H
#define CPPMICROSERVICES_HTTPSERVLETREQUESTPRIVATE_H

#include "cppmicroservices/SharedData.h"
#include "cppmicroservices/httpservice/IHttpServletPart.h"

#include <map>
#include <memory>
#include <string>

#include "HttpServletPartPrivate.h"
class CivetServer;
struct mg_connection;

namespace cppmicroservices {

class Any;
class ServletContext;
class HttpServletPart;

struct HttpServletRequestPrivate : public SharedData
{
  HttpServletRequestPrivate(std::shared_ptr<ServletContext> servletContext,
                            CivetServer* server,
                            mg_connection* conn);

  ~HttpServletRequestPrivate();

  const std::shared_ptr<ServletContext> m_ServletContext;
  CivetServer* const m_Server;
  struct mg_connection* const m_Connection;

  std::string m_Scheme;
  std::string m_ServerName;
  std::string m_ServerPort;
  std::string m_Uri;
  std::string m_ContextPath;
  std::string m_ServletPath;
  std::string m_PathInfo;
  std::string m_QueryString;
  std::string m_Url;

  std::string m_TempDirname;

  typedef std::map<std::string, IHttpServletPart*> PartsMapType;
  PartsMapType m_PartsMap;

  typedef std::map<std::string, Any> AttributeMapType;
  AttributeMapType m_Attributes;

  typedef std::map<std::string, std::string> ParameterMapType;
  ParameterMapType m_Parameters;

  /*!
   * Splits a query string (using & separator) and assign each key/value in the
   * request
   * attributes.
   *
   * Note: string is considered to be sanitized
   */
  void ExtractAttributesFromQueryString(const std::string& queryString);
};
}

#endif // CPPMICROSERVICES_HTTPSERVLETREQUESTPRIVATE_H
