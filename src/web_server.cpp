#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include "httplib.h"
#include "apartment.h"
#include "evaluator.h"

std::string generateHTML(const std::vector<Apartment>& apartments, const Weights& weights) {
    std::stringstream html;
    html << "<!DOCTYPE html>\n"
         << "<html>\n"
         << "<head>\n"
         << "    <title>Apartment Evaluator Web</title>\n"
         << "    <style>\n"
         << "        body { font-family: Arial, sans-serif; margin: 20px; }\n"
         << "        .container { max-width: 800px; margin: 0 auto; }\n"
         << "        .apartment { border: 1px solid #ddd; padding: 10px; margin: 10px 0; }\n"
         << "        .form-group { margin: 10px 0; }\n"
         << "        input, button { padding: 8px; margin: 5px; }\n"
         << "        button { background: #007bff; color: white; border: none; cursor: pointer; }\n"
         << "        button:hover { background: #0056b3; }\n"
         << "        .weights { background: #f8f9fa; padding: 10px; margin: 10px 0; }\n"
         << "    </style>\n"
         << "</head>\n"
         << "<body>\n"
         << "    <div class=\"container\">\n"
         << "        <h1>Apartment Evaluation System</h1>\n"
         << "        \n"
         << "        <div class=\"weights\">\n"
         << "            <h3>Current Weights</h3>\n"
         << "            <p>Price: " << (weights.price * 100) << "%,\n"
         << "            Space: " << (weights.space * 100) << "%,\n"
         << "            Noise: " << (weights.noise * 100) << "%</p>\n"
         << "        </div>\n"
         << "        \n"
         << "        <h2>Add Apartment</h2>\n"
         << "        <form method=\"POST\" action=\"/add\">\n"
         << "            <div class=\"form-group\">\n"
         << "                <input type=\"text\" name=\"id\" placeholder=\"Apartment ID\" required>\n"
         << "            </div>\n"
         << "            <div class=\"form-group\">\n"
         << "                <input type=\"number\" name=\"price\" placeholder=\"Monthly Price ($)\" step=\"0.01\" required>\n"
         << "            </div>\n"
         << "            <div class=\"form-group\">\n"
         << "                <input type=\"number\" name=\"space\" placeholder=\"Space (sqft)\" required>\n"
         << "            </div>\n"
         << "            <div class=\"form-group\">\n"
         << "                <input type=\"number\" name=\"noise\" placeholder=\"Noise Level (0-100)\" min=\"0\" max=\"100\" required>\n"
         << "            </div>\n"
         << "            <button type=\"submit\">Add Apartment</button>\n"
         << "        </form>\n"
         << "        \n"
         << "        <h2>Customize Weights</h2>\n"
         << "        <form method=\"POST\" action=\"/weights\">\n"
         << "            <div class=\"form-group\">\n"
         << "                <input type=\"number\" name=\"price\" placeholder=\"Price Weight (0-1)\" step=\"0.01\" min=\"0\" max=\"1\" required>\n"
         << "            </div>\n"
         << "            <div class=\"form-group\">\n"
         << "                <input type=\"number\" name=\"space\" placeholder=\"Space Weight (0-1)\" step=\"0.01\" min=\"0\" max=\"1\" required>\n"
         << "            </div>\n"
         << "            <div class=\"form-group\">\n"
         << "                <input type=\"number\" name=\"noise\" placeholder=\"Noise Weight (0-1)\" step=\"0.01\" min=\"0\" max=\"1\" required>\n"
         << "            </div>\n"
         << "            <button type=\"submit\">Update Weights</button>\n"
         << "        </form>\n"
         << "        \n"
         << "        <h2>Load Apartments from File</h2>\n"
         << "        <form method=\"POST\" action=\"/load\" enctype=\"multipart/form-data\">\n"
         << "            <div class=\"form-group\">\n"
         << "                <input type=\"file\" name=\"file\" accept=\".csv\" required>\n"
         << "            </div>\n"
         << "            <button type=\"submit\">Load File</button>\n"
         << "        </form>\n"
         << "        \n"
         << "        <h2>Apartments</h2>\n"
         << "        <div id=\"apartments\">\n";

    for (const auto& apt : apartments) {
        html << "        <div class=\"apartment\">\n"
             << "            <strong>" << apt.getId() << "</strong> - \n"
             << "            $" << apt.getPrice() << "/month, \n"
             << "            " << apt.getSpace() << " sqft, \n"
             << "            Noise: " << apt.getNoise() << "\n"
             << "        </div>\n";
    }

    html << "        </div>\n"
         << "        \n"
         << "        <h2>Ranking</h2>\n"
         << "        <form method=\"GET\" action=\"/rank\">\n"
         << "            <button type=\"submit\">Rank Apartments</button>\n"
         << "        </form>\n"
         << "        \n"
         << "        <div id=\"ranking\"></div>\n"
         << "        \n"
         << "        <script>\n"
         << "            function updateApartments() {\n"
         << "                fetch('/apartments')\n"
         << "                    .then(response => response.text())\n"
         << "                    .then(html => document.getElementById('apartments').innerHTML = html);\n"
         << "            }\n"
         << "            \n"
         << "            function updateRanking() {\n"
         << "                fetch('/ranking')\n"
         << "                    .then(response => response.text())\n"
         << "                    .then(html => document.getElementById('ranking').innerHTML = html);\n"
         << "            }\n"
         << "            \n"
         << "            // Auto-refresh apartments every 2 seconds\n"
         << "            setInterval(updateApartments, 2000);\n"
         << "        </script>\n"
         << "    </div>\n"
         << "</body>\n"
         << "</html>\n";
    return html.str();
}

std::string generateApartmentsHTML(const std::vector<Apartment>& apartments) {
    std::stringstream html;
    for (const auto& apt : apartments) {
        html << "<div class='apartment'>"
             << "<strong>" << apt.getId() << "</strong> - "
             << "$" << apt.getPrice() << "/month, "
             << apt.getSpace() << " sqft, "
             << "Noise: " << apt.getNoise()
             << "</div>";
    }
    return html.str();
}

std::string generateRankingHTML(const std::vector<Apartment>& apartments, const Evaluator& evaluator) {
    if (apartments.empty()) {
        return "<p>No apartments to rank.</p>";
    }
    
    auto ranked = evaluator.rankApartments(apartments);
    std::stringstream html;
    html << "<ol>";
    for (size_t i = 0; i < ranked.size(); ++i) {
        html << "<li>" << ranked[i].getId() << "</li>";
    }
    html << "</ol>";
    return html.str();
}

int main() {
    std::vector<Apartment> apartments;
    Weights currentWeights(0.4, 0.35, 0.25);
    Evaluator evaluator(currentWeights);
    
    httplib::Server svr;
    
    // Serve main page
    svr.Get("/", [&](const httplib::Request&, httplib::Response& res) {
        res.set_content(generateHTML(apartments, currentWeights), "text/html");
    });
    
    // Add apartment
    svr.Post("/add", [&](const httplib::Request& req, httplib::Response& res) {
        auto id = req.get_param_value("id");
        auto price_str = req.get_param_value("price");
        auto space_str = req.get_param_value("space");
        auto noise_str = req.get_param_value("noise");
        
        try {
            double price = std::stod(price_str);
            double space = std::stod(space_str);
            double noise = std::stod(noise_str);
            
            apartments.emplace_back(id, price, space, noise);
            res.set_redirect("/");
        } catch (...) {
            res.status = 400;
            res.set_content("Invalid input data", "text/plain");
        }
    });
    
    // Update weights
    svr.Post("/weights", [&](const httplib::Request& req, httplib::Response& res) {
        auto price_str = req.get_param_value("price");
        auto space_str = req.get_param_value("space");
        auto noise_str = req.get_param_value("noise");
        
        try {
            double price_w = std::stod(price_str);
            double space_w = std::stod(space_str);
            double noise_w = std::stod(noise_str);
            
            double total = price_w + space_w + noise_w;
            if (total > 0) {
                currentWeights = Weights(price_w / total, space_w / total, noise_w / total);
                evaluator.setWeights(currentWeights);
                res.set_redirect("/");
            } else {
                res.status = 400;
                res.set_content("Weights must sum to a positive value", "text/plain");
            }
        } catch (...) {
            res.status = 400;
            res.set_content("Invalid weight values", "text/plain");
        }
    });
    
    // Get apartments list
    svr.Get("/apartments", [&](const httplib::Request&, httplib::Response& res) {
        res.set_content(generateApartmentsHTML(apartments), "text/html");
    });
    
    // Get ranking
    svr.Get("/rank", [&](const httplib::Request&, httplib::Response& res) {
        res.set_content(generateRankingHTML(apartments, evaluator), "text/html");
    });
    
    // Load from file (simplified - would need proper file upload handling)
    svr.Post("/load", [&](const httplib::Request& req, httplib::Response& res) {
        // For simplicity, just redirect - file upload would need more complex handling
        res.set_content("File upload not implemented in this demo", "text/plain");
    });
    
    std::cout << "Web server starting on http://localhost:8080\n";
    std::cout << "Press Ctrl+C to stop\n";
    
    svr.listen("0.0.0.0", 8080);
    
    return 0;
}