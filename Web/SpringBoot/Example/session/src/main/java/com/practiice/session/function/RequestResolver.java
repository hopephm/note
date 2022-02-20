package com.practiice.session.function;

import org.springframework.stereotype.Component;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.util.Enumeration;

@Component
public class RequestResolver {
    public String getRequestInfo(HttpServletRequest request){
        String rst = "Headers{ <br/>";

        Enumeration<String> headers = request.getHeaderNames();
        while(headers.hasMoreElements()){
            String header = headers.nextElement();
            rst += header + ": ";
            rst += request.getHeader(header);
            rst += "<br/>";

        }
        rst += "}<br/><br/><br/>";

        String query= request.getQueryString();

        rst += "Query{ <br/>";
        rst += query;
        rst += "<br/>}<br/><br/><br/>";

        HttpSession session = request.getSession();
        Enumeration<String> keys = session.getAttributeNames();

        rst += "Session{ <br/>";
        while(keys.hasMoreElements()){
            String key = keys.nextElement();
            rst += key + ": ";
            rst += session.getAttribute(key);
            rst += "<br/>";
        }
        rst += "}<br/><br/><br/>";

        return rst;
    }
}
