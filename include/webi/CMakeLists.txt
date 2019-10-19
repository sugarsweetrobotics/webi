set(headers webi.h html.h css.h client.h bootstrap.h
            http_server.h remote_dom.h response.h server.h
            webi_common.h websocket_server.h xml.h
)
message("headers = ${headers}")

set(webi_hdrs)
foreach(v ${headers}) 
  message("v = ${v}")
  list(APPEND webi_hdrs ${CMAKE_CURRENT_SOURCE_DIR}/${v})  
endforeach(v in lists headers)

message("webi_hdrs= ${webi_hdrs}")

set(webi_headers ${webi_hdrs} PARENT_SCOPE)