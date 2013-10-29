/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "otbMacro.h"
#include "otbPostGISConnectionImplementation.h"

class ReadTables : public pqxx::transactor<pqxx::nontransaction>
{
  pqxx::result m_Result;
public:
  ReadTables() : pqxx::transactor<pqxx::nontransaction>("ReadTables") {}

  void operator ()(argument_type& T)
  {
    m_Result = T.exec("SELECT * FROM pg_tables");
  }

  void on_commit()
  {
    for (pqxx::result::const_iterator c = m_Result.begin(); c != m_Result.end(); ++c)
      {
      std::string N;
      c[0].to(N);

      std::cout << '\t' << c.num() << '\t' << N << std::endl;
      }
  }
};

int otbPostGISConnectionImplementationPerformTransaction(int argc, char * argv[])
{

  const std::string hostName = argv[1];
  const std::string dbName = argv[2];
  const std::string userName = argv[3];
  const std::string userPassword = argv[4];

  typedef otb::PostGISConnectionImplementation GISConnectionType;

  //Instantiation
  GISConnectionType::Pointer connection = GISConnectionType::New();

  connection->SetHost(hostName);
  connection->SetDBName(dbName);
  connection->SetUser(userName);
  connection->SetPassword(userPassword);

  connection->ConnectToDB();

  connection->GetConnection()->perform(ReadTables());

  return EXIT_SUCCESS;
}