package example;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet("/DemoServlet")
public class DemoServlet extends HttpServlet {
  private static final long serialVersionUID = 1L;

  protected void doGet(HttpServletRequest request, HttpServletResponse response)
                        throws ServletException, IOException {
    response.setContentType("text/html");
    PrintWriter pw = response.getWriter();

    pw.println("<h1>So, this is a Dynamic Web project</h1>");
    pw.println("<p>Created my first servlet program on the Eclipse IDE</p>");
    pw.println("<p>And got it running successfully</p>");
    pw.println("<a href=index.jsp>back to home</a>");
  }

  protected void doPost(HttpServletRequest request, HttpServletResponse response)
                          throws ServletException, IOException {
    doGet(request, response);
  }
}