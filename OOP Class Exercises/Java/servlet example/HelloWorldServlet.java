package com.example;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

// URL mapping to "/hello"
@WebServlet("/hello")
public class HelloWorldServlet extends HttpServlet {
    
    private static final long serialVersionUID = 1L;

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/html");
        
        // Write response
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Hello, World!</h1>");
        response.getWriter().println("</body></html>");
    }
}
