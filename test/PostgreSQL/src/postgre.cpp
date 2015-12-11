#include "../include/postgre.hpp"

Postgre::Postgre(char *dbname, char *user, char *password, char *ip, char *port) {

  if (setDbName(dbname) == false)
    throw ;
  std::cout << "DbName : " <<this->DbName_ << std::endl;
  if (setUser(user) == false)
    throw ;
  std::cout << "User : " <<this->User_ << std::endl;
  if (setPasswd(password) == false)
    throw ;
  std::cout << "Passwd : " <<this->Passwd_ << std::endl;
  if (setIp(ip) == false)
    throw ;
  std::cout << "Ip : " <<this->Ip_ << std::endl;
  setPort(atoi(port));
  std::cout << "Port : " <<this->Port_ << std::endl;

  std::cout << "CONSTRUCTOR OK" << std::endl << std::endl;
}


Postgre::~Postgre() {
  
  free(this->DbName_);
  free(this->User_);
  free(this->Passwd_);
  free(this->Ip_);

  std::cout << std::endl << "DESTRUCTOR OK" << std::endl;
}

void		Postgre::run() {

  std::cout << "POSTGRE GO >>>" << std::endl;

  /**
   * Convert our DbName_ to be readable by PQconnectdb
   */
  if (setConninfo() == false)
    throw ;
  else
    std::cout << "Conninfo : " << this->conninfo << std::endl;

  /**
   * Connection to the database
   */
  this->conn = PQconnectdb(getConninfo());

  /**
   * Checking if the connection is Ok
   */
  if (PQstatus(conn) != CONNECTION_OK) {
    fprintf(stderr, "Connection to database failed: %s",
	    PQerrorMessage(conn));
    throw ;
  } else
    std::cout << "Connection to database : Ok" << std::endl;

  








  return ;
}

bool		Postgre::setDbName(char *db) {
  if ((this->DbName_ = (char *)malloc(sizeof(char *) * 4096)) == NULL)
    return false;
  strcpy(this->DbName_, db);
  return true;
}

char		*Postgre::getDbName() const  {
  return this->DbName_;
}

bool		Postgre::setUser(char *user) {
  if ((this->User_ = (char *)malloc(sizeof(char *) * 4096)) == NULL)
    return false;
  strcpy(this->User_, user);
  return true;
}

char		*Postgre::getUser() const {
  return this->User_;
}

bool		Postgre::setPasswd(char *pass) {
  if ((this->Passwd_ = (char *)malloc(sizeof(char *) * 4096)) == NULL)
    return false;
  strcpy(this->Passwd_, pass);
  return true;
}

char		*Postgre::getPasswd() const {
  return this->Passwd_;
}

bool		Postgre::setIp(char *ip) {
  if ((this->Ip_ = (char *)malloc(sizeof(char *) * 4096)) == NULL)
    return false;
  strcpy(this->Ip_, ip);
  return true;
}

char		*Postgre::getIp() const {
  return this->Ip_;
}

void		Postgre::setPort(int port) {
  this->Port_ = port;
}

int		Postgre::getPort() const {
  return this->Port_;
}

bool		Postgre::setConninfo() {
  if (this->DbName_ == NULL)
    return false;

  if ((this->conninfo = (char *)malloc(sizeof(char *) * 4096)) == NULL)
    return false;
  strcpy(this->conninfo, "dbname = ");
  
  int i = 0;
  while (this->conninfo[i] != '\0')
    i++;

  int j = 0;
  while (this->DbName_[j] != '\0') {
    this->conninfo[i] = this->DbName_[j];
    i++;
    j++;
  }
  return true;
}

char		*Postgre::getConninfo() const {
  return this->conninfo;
}
