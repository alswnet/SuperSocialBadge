
#ifdef FacebookID
#include <FacebookApi.h>//Libreria de Facebook
FacebookApi *apifb;

void IniciarFacebook() {
  apifb = new FacebookApi(client, Facebook_KEY);
}

//Consulta para buscar los seguidores una Fanpage de Facebook
boolean getFacebook() {
  int pageLikes = apifb->getPageFanCount(FacebookID);
  if (Sub[Facebook] < pageLikes) {
    Sub[Facebook] = pageLikes;
    Serial.print("Facebook: ");
    Serial.println(Sub[Facebook]);
    return true;
  }
  return false;
}
#endif

