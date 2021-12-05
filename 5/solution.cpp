#include <iostream>
#include <istream>
#include <unordered_map>
#include <vector>

using namespace std;

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}

    bool operator==(const Point& other) const {
        return (other.x == x) && (other.y == y);
    }

    bool operator!=(const Point& other) const { return !(*this == other); }
};

struct PointHasher {
    size_t operator()(const Point& point) const {
        return point.x * 1000 + point.y;
    }
};

typedef unordered_map<Point, int, PointHasher> GridMap;

struct Line {
    Point start, end;
    Line() {}
    Line(Point start, Point end) : start(start), end(end) {}

    bool is_straight() { return start.x == end.x || start.y == end.y; }

    bool is_diagonal() { return abs(end.y - start.y) == abs(end.x - start.x); }
};

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "(" << point.x << "," << point.y << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Line& line) {
    os << line.start << " -> " << line.end;
    return os;
}

std::ostream& operator<<(std::ostream& os, const vector<vector<int>>& grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            os << grid[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

vector<Line> read_input() {
    string input;

    vector<Line> parsed_input;

    while (!cin.eof()) {
        Point p1;
        Point p2;
        getline(cin, input, ',');
        p1.x = stoi(input);
        cin >> p1.y;

        cin >> input;  // -> char

        getline(cin, input, ',');
        p2.x = stoi(input);
        cin >> p2.y;

        Line l(p1, p2);

        parsed_input.push_back(l);
    }

    return parsed_input;
}

int sign(int x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

void trace_line(GridMap& grid, Line l) {
    if (l.is_diagonal() || l.is_straight()) {
        Point p(l.start);

        cout << p << endl;

        int x_diff = l.end.x - l.start.x;
        int y_diff = l.end.y - l.start.y;

        while (p != l.end) {
            grid[p] += 1;
            p.x += sign(x_diff);
            p.y += sign(y_diff);
        }
        grid[p] += 1;
    }
}

int main() {
    vector<Line> lines = read_input();

    GridMap grid;

    for (auto l : lines) {
        trace_line(grid, l);
    }

    int answer = 0;

    for (auto& cell : grid) {
        if (cell.second >= 2) {
            answer++;
        }
    }

    cout << "Answer : " << answer << endl;
}