
String Html_Config() {

  String html = "<html>"
  "<head>"
  "<title>Camera Slider</title>"
  "<style>"
  "body {background:#2d343d;font-size:6vw;}"
  "input, select {width:40%;height:6vw;padding-left:1vw;background:#fff;font-size:4vw;}"
  "a {color:#fff;text-decoration:none;margin:2vw;text-align:center;background:#f0776c;height:6vw;padding:1vw 0;}"
  "</style>"
  "</head>"
  "<body>"
  "<form style=\"margin:2vw auto;width:75vw;padding:3vw 2vw;background:white;\">"
  " <h3>Distance:</h3>"
  " <input type=\"number\" name=\"distance\" value=\"" + String(distance) + "\">"
  " <select name=\"distance_mm_multiplier\">"
  "  <option value=\"1\" " + String(distance_mm_multiplier == (float)1 ? "selected=\"true\"" : "") + ">millimeters</option>"
  "  <option value=\"10\" " + String(distance_mm_multiplier == (float)10 ? "selected=\"true\"" : "") + ">centimeters</option>"
  " </select>"
  " <h3>Duration:</h3>"
  " <input type=\"number\" name=\"duration\" value=\"" + String(duration) + "\">"
  " <select name=\"duration_sec_multiplier\">"
  "  <option value=\"1\" " + String(duration_sec_multiplier == (float)1 ? "selected=\"true\"" : "") + ">seconds</option>"
  "  <option value=\"60\" " + String(duration_sec_multiplier == (float)60 ? "selected=\"true\"" : "") + ">minutes</option>"
  " </select>"
  " <h3>Direction:</h3>"
  " <select style=\"width:100%;\" name=\"direction\">"
  "  <option value=\"1\">From A to B</option>"
  "  <option value=\"-1\">From B to A</option>"
  " </select>"
  " <input type=\"submit\" value=\"Lets Go\" style=\"font-size:6vw;width:100%;height:7vw;color:#fff;text-align:center;background:#f0776c;\">"
  " <h3>Go to:</h3>"
  " <a href=\"/gotoa\">&nbsp;<<< A <<<&nbsp;</a>"
  " <a href=\"/gotob\">&nbsp;>>> B >>>&nbsp;</a>"
  "</form>"
  "</body>"
  "</html>";

  return html;
}

