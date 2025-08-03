module;
#include <type_traits>

export module mite.point;

export namespace mite {

    template<typename  T>
    struct Point {
        static_assert(std::is_arithmetic_v<T>, "Point must be of an arithmetic type");

    protected:
        T x_;
        T y_;

    public:

        explicit Point(T x = 0, T y = 0) : x_(x), y_(y) {}

        // Addition operator
        Point operator+(const Point& other) const {
            return Point(x_ + other.x_, y_ + other.y_);
        }

        Point& operator+=(const Point& other) {
            x_ += other.x_;
            y_ += other.y_;
            return *this;
        }

        // Subtraction operator
        Point operator-(const Point& other) const {
            return Point(x_ - other.x_, y_ - other.y_);
        }

        Point& operator-=(const Point& other) {
            x_ -= other.x_;
            y_ -= other.y_;
            return *this;
        }

        // Scalar multiplication
        Point operator*(T scalar) const {
            return Point(x_ * scalar, y_ * scalar);
        }

        // Scalar division
        Point operator/(T scalar) const {
            return Point(x_ / scalar, y_ / scalar);
        }

        // Equality operator
        bool operator==(const Point& other) const {
            return x_ == other.x_ && y_ == other.y_;
        }

        // Inequality operator
        bool operator!=(const Point& other) const {
            return !(*this == other);
        }

        T x() const {
            return x_;
        }

        T y() const {
            return y_;
        }


        Point& at_x(T new_x) {
            x_ = new_x;
            return *this;
        }

        Point& at_y(T new_y) {
            y_ = new_y;
            return *this;
        }

        template<typename U>
        U distance_from(const Point<U>& other) const {
            U dx = static_cast<U>(other.x() - static_cast<U>(x_));
            U dy = static_cast<U>(other.y() - static_cast<U>(y_));
            return static_cast<U>(sqrt(dx * dx + dy * dy));
        }

        template<typename U>
        U distance_from(const Point<U> other) const {
            U dx = static_cast<U>(other.x() - static_cast<U>(x_));
            U dy = static_cast<U>(other.y() - static_cast<U>(y_));
            return static_cast<U>(sqrt(dx * dx + dy * dy));
        }

        template<typename U>
        U y_from(const Point<U>& other) const {
            return static_cast<U>(other.y() - y_);
        }

        template<typename U>
        U y_from(const Point<U> other) const {
            return static_cast<U>(other.y() - y_);
        }

        template<typename U>
        U x_from(const Point<U>& other) const {
            return static_cast<U>(other.x() - x_);
        }

        template<typename U>
        U x_from(const Point<U> other) const {
            return static_cast<U>(other.x() - x_);
        }

        template<typename U>
        Point<U> cast() const {
            return Point<U>(static_cast<U>(x_), static_cast<U>(y_));
        }

    };

    namespace point {
        template<typename T>
    concept HasXPosMember = requires(T t) {
            t.x;
    };

        template<typename T>
        concept HasXposMethod = requires(T t) {
            t.y();
        };

        template<typename T>
        concept HasXPos = HasXPosMember<T> || HasXposMethod<T>;

        template<typename T>
        concept HasYPosMember = requires(T t) {
            t.y;
        };

        template<typename T>
        concept HasYposMethod = requires(T t) {
            t.y();
        };

        template<typename T>
        concept HasYPos = HasYPosMember<T> || HasYposMethod<T>;
    }

    template<typename T>
    concept IsPoint = point::HasXPos<T> && point::HasYPos<T>;

} // namespace mite