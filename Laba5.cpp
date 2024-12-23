// �?нтерфейс для создания HTML-элементов
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept> // Добавлено для использования invalid_argument
using namespace std;


// �?нтерфейс для создания HTML-элементов
class HtmlElement {
public:
    virtual string render() const = 0;
    virtual ~HtmlElement() = default;
};

class HtmlHeader : public HtmlElement {
private:
    string text;
    int level; // Уровень заголовка (1-6)
public:
    HtmlHeader(const string& text, int level) : text(text), level(level) {
        if (level < 1 || level > 6) {
            throw invalid_argument("Level must be between 1 and 6");
        }
    }

    string render() const override {
        return "<div style='text-align: center;'><h" + to_string(level) + ">" + text + "</h" + to_string(level) + "></div>\n";
    }
};
// Класс для текста
class HtmlText : public HtmlElement {
private:
    string text;
public:
    HtmlText(const string& text) : text(text) {}

    string render() const override {
        return "<p>" + text + "</p>\n";
    }
};

// Класс для таблицы
class HtmlTable : public HtmlElement {
private:
    vector<vector<string>> data;
public:
    HtmlTable(const vector<vector<string>>& data) : data(data) {}

    string render() const override {
        string html = "<table border='1'>\n";
        for (const auto& row : data) {
            html += "  <tr>\n";
            for (const auto& cell : row) {
                html += "    <td>" + cell + "</td>\n";
            }
            html += "  </tr>\n";
        }
        html += "</table>\n";
        return html;
    }
};

// Класс для диаграммы
class HtmlChart : public HtmlElement {
private:
    string imagePath;
    string title;
public:
    HtmlChart(const string& imagePath, const string& title) : imagePath(imagePath), title(title) {}

    string render() const override {
        return "<div style='text-align: center;'><img src='" + imagePath + "' alt='Chart'><h4>" + title + "</h4></div>\n";
    }
};

// Класс для скриншота
class HtmlScreenshot : public HtmlElement {
private:
    string imagePath;
    string title;
public:
    HtmlScreenshot(const string& imagePath, const string& title) 
        : imagePath(imagePath), title(title) {}

    string render() const override {
        return "<div style='text-align: center;'><img src='" + imagePath + "' alt='Screenshot'><h4>" + title + "</h4></div>\n";
    }
};

// Класс строителя отчета
class ReportBuilder {
private:
    vector<unique_ptr<HtmlElement>> elements;
public:
    void addHeader(const string& text, int level) {
        elements.push_back(make_unique<HtmlHeader>(text, level));
    }

    void addText(const string& text) {
        elements.push_back(make_unique<HtmlText>(text));
    }

    void addTable(const vector<vector<string>>& data) {
        elements.push_back(make_unique<HtmlTable>(data));
    }

    void addChart(const string& imagePath, const string& title) {
        elements.push_back(make_unique<HtmlChart>(imagePath, title));
    }

    void addScreenshot(const string& imagePath, const string& title) {
        elements.push_back(make_unique<HtmlScreenshot>(imagePath, title));
    }

    string build() const {
        string html = "<html><body>\n";
        for (const auto& element : elements) {
            html += element->render();
        }
        html += "</body></html>\n";
        return html;
    }
};

class Prog : public ReportBuilder {
public:
    Prog() {
    addHeader("Отчёт по программированию", 1);
    addHeader("Паттерны", 2);
    addText("Цели задачи всякое такое.");
    addHeader("Наглядное представление", 3);
    addText("Подробная таблица.");
    addTable({
        {"Итог по лабораторным работам н-ного студента"},
        {"Лабораторная работа", "Оценка", "Оценка2"},
        {"1", "5", "4"},
        {"2", "4", "4"},
        {"3", "5", "4"}
    });
    addHeader("Перейдём к диаграммам", 3);
    addChart("1.PNG", "Диаграмма 1.1 -- Диграмма по кварталам за 2024 год");
    addHeader("Рисунки", 3);
    addText("Текст задания.");
    addScreenshot("2.jpg", "Рисунок 1.1 -- Алгоритм решения трудной задачи");
    
    addHeader("Заключение", 1);
    addText("В заключении стоит сказать что было проделана большая работа по формированию этого отчёта)))");
    }
};

class Inf : public ReportBuilder {
public:
    Inf() {
    addHeader("отчёт по информатике", 1);
    addHeader("Итерационные циклы", 2);
    addText("Задание : Вычислить приближенное значение заданной функции через степенной ряд. Вычисляя степенной ряд, использовать итерационный способ накопления");
    addHeader("Наглядное представление", 3);
    addText("Подробная таблица.");
    addTable({
        {"Этапы итерационного"},
        {"Этапы итерационного цикла", "Цели", "Методы","Примеры проектов"},
        {"Планирование", "Определение задач", "	Брейнсторминг","Разработка ПО"},
        {"Разработка", "Создание прототипа", "Agile, Scrum","Веб-приложение"},
        {"Тестирование", "Проверка качества", "Юнит-тестирование","Мобильное приложение"}
    });
    addHeader("Перейдём к диаграммам", 3);
    addChart("1.PNG", "Диаграмма 1.1 -- Итерационные циклы");
    addHeader("Рисунки", 3);
    addText("Текст задания.");
    addScreenshot("2.jpg", "Рисунок 1.1 -- Алгоритм решения задачи");
    
    addHeader("Заключение", 1);
    addText("С приближением x к 1 ряд сходимость ряда значительно  увеличивается. При увеличении x число шагов, необходимых для достижения требуемой точности, увеличивается.");
    }
};

class Technical : public ReportBuilder {
public:
    Technical() {
    addHeader("Отчёт по технологиям и методам программирования", 1);
    addHeader("Тема", 2);
    addText("Задание:Дополнение до квадрата. «Какое число – спросил полковник Крэкхэм, - обладает тем свойством, что если его прибавить к числам 100 и 164 в отдельности, то каждый раз получаются точные квадраты?»");
    addText("Программа должна выполнять линейный перебор всех чисел, при сложении которых к числам 100 и 164 по отдельности получатся точные квадраты. В конечном итоге программа должны вывести найденное число.  ");
    addHeader("Основные идеи выполнения задания.Есть два варианта выполнения задания: либо линейно прибавлять все числа к 100 и 164 по отдельности и извлекать из них корень квадратный, либо линейно отнимать и извлекать из них корень квадратный, но в таком случае нам нужно создать доп  условие , т.к невозможно вычислисть корень квадратный из отрицательного числа.", 1);
    addText("Подробная таблица.");
    addTable({
        {"Итог по лабораторным работам н-ного студента"},
        {"Лабораторная работа", "Оценка", "Оценка2"},
        {"1", "5", "4"},
        {"2", "4", "4"},
        {"3", "5", "4"}
    });
    addHeader("Перейдём к диаграммам", 3);
    addChart("3.PNG", "Диаграмма 1.1 -- Диграмма по кварталам за 2024 год");
    addHeader("Рисунки", 3);
    addScreenshot("2.jpg", "Рисунок 1.1 -- Алгоритм решения трудной задачи");
    
    addHeader("Заключение", 1);
    addText("В заключении стоит сказать что было проделана большая работа по формированию этого отчёта)))");
    }
};

// Пример использования
int main() {
    unique_ptr<ReportBuilder> progReport = make_unique<Prog>();
    unique_ptr<ReportBuilder> infReport = make_unique<Inf>();
    unique_ptr<ReportBuilder> technicalReport = make_unique<Technical>();

    string ProgHtml = progReport->build();
    string InfHtml = infReport->build();
    string TechnicalHtml = technicalReport->build();

    // Записываем отчеты в файлы
    ofstream techFile("Prog_report.html");
    ofstream finFile("Inf_report.html");
    ofstream sumFile("Technical_report.html");

    if (techFile.is_open()) {
        techFile << ProgHtml;
        techFile.close();
        cout << "Отчёт по программированию успешно записан в файл technical_report.html" << endl;
    }
    if (finFile.is_open()) {
        finFile << InfHtml;
        finFile.close();
        cout << "Отчёт по информатике успешно записан в файл financial_report.html" << endl;
    }
    if (sumFile.is_open()) {
        sumFile << TechnicalHtml;
        sumFile.close();
        cout << "Отчёт по технологиям и методам программирования успешно записан в файл summary_report.html" << endl;
    }

    return 0;
}