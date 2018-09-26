#ifdef YoutubeID

#include <YoutubeApi.h> //Libreria de Youtube
YoutubeApi api(YOUTUBE_KEY, client);

//TODO Guardas SD
//Consulta para buscar cuantos subcriptores en Youtube
boolean getYoutube() {

  int subYoutube = Sub[Youtube];
  if (api.getChannelStatistics(YoutubeID)) {
    subYoutube = api.channelStats.subscriberCount;
  }

  if (Sub[Youtube] < subYoutube) {
    Sub[Youtube] = subYoutube;
    Serial.print("Youtube: ");
    Serial.println(Sub[Youtube]);
    return true;
  } else if (Sub[Youtube] > subYoutube) {
    Sub[Youtube] = subYoutube;
  }
  return false;
}

#endif
