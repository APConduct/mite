module;
#include <type_traits>

export module mite.square;

import mite.size;
import mite.point;

export namespace mite {


    /**
     * @brief A template class representing a 2D square with geometric operations.
     * @tparam T The type of the coordinates and dimensions, must be an arithmetic type.
     */
    template <typename T>
    struct Square {
        static_assert(std::is_arithmetic_v<T>, "Square must be of an arithmetic type");

    protected:
        flat::Point<T> origin_; ///< The origin point (bottom-left corner) of the square.
        T len_; ///< The side length of the square.

    public:

        /**
         * @brief Constructs a Square with given origin point and side length.
         * @param origin The origin point of the square (default is Point at 0,0).
         * @param len The side length of the square (default is 0).
         */
        explicit Square(flat::Point<T> origin = flat::Point<T>(), T len = 0)
            : origin_(origin), len_(len) {}


        /**
         * @brief Gets the origin point of the square.
         * @return The origin point of the square.
         */
        flat::Point<T> origin() const {
            return origin_;
        }


        /**
         * @brief Gets the side length of the square.
         * @return The side length of the square.
         */
        T length() const {
            return len_;
        }

        /**
         * @brief Gets the width of the square (same as length for a square).
         * @return The width of the square.
         */
        T width() const {
            return len_;
        }

        /**
         * @brief Sets the origin point of the square.
         * @param new_origin The new origin point.
         */
        void set_origin(const flat::Point<T>& new_origin) {
            origin_ = new_origin;
        }


        /**
         * @brief Sets the side length of the square.
         * @param new_len The new side length.
         */
        void set_length(T new_len) {
            len_ = new_len;
        }

        /**
         * @brief Gets the x-coordinate of the square's origin.
         * @return The x-coordinate of the origin point.
         */
        T x() const {
            return origin_.x();
        }

        /**
         * @brief Gets the y-coordinate of the square's origin.
         * @return The y-coordinate of the origin point.
         */
        T y() const {
            return origin_.y();
        }

        /**
         * @brief Sets the x-coordinate of the square's origin.
         * @param new_x The new x-coordinate.
         * @return A reference to this square for method chaining.
         */
        Square& at_x(T new_x) {
            origin_.at_x(new_x);
            return *this;
        }

        /**
         * @brief Sets the y-coordinate of the square's origin.
         * @param new_y The new y-coordinate.
         * @return A reference to this square for method chaining.
         */
        Square& at_y(T new_y) {
            origin_.at_y(new_y);
            return *this;
        }

        /**
         * @brief Sets the origin point of the square.
         * @param new_origin The new origin point.
         * @return A reference to this square for method chaining.
         */
        Square & at(const flat::Point<T>& new_origin) {
            origin_ = new_origin;
            return *this;
        }


        /**
         * @brief Checks if two squares are equal.
         * @param other The other square to compare.
         * @return True if the squares have the same origin and length, false otherwise.
         */
        bool operator==(const Square& other) const {
            return origin_ == other.origin_ && len_ == other.len_;
        }


        /**
         * @brief Checks if two squares are not equal.
         * @param other The other square to compare.
         * @return True if the squares are not equal, false otherwise.
         */
        bool operator!=(const Square& other) const {
            return !(*this == other);
        }


        /**
         * @brief Calculates the area of the square.
         * @return The area of the square (length squared).
         */
        T area() const {
            return len_ * len_;
        }


        /**
         * @brief Checks if this square can fit another square within its bounds.
         * @param other The other square to check.
         * @return True if the other square can fit entirely within this square, false otherwise.
         */
        bool can_fit(const Square& other) const {
            return other.origin_.x() >= origin_.x() &&
                   other.origin_.y() >= origin_.y() &&
                   (other.origin_.x() + other.len_) <= (origin_.x() + len_) &&
                   (other.origin_.y() + other.len_) <= (origin_.y() + len_);
        }


        /**
         * @brief Checks if a point is contained within the square.
         * @param point The point to check.
         * @return True if the point is within the square's bounds (inclusive), false otherwise.
         */
        bool contains(const flat::Point<T>& point) const {
            return point.x() >= origin_.x() && point.x() <= (origin_.x() + len_)
                && point.y() >= origin_.y() && point.y() <= (origin_.y() + len_);
        }


        /**
         * @brief Checks if this square intersects with another square.
         * @param other The other square to check for intersection.
         * @return True if the squares intersect, false otherwise.
         */
        bool intersects(const Square& other) const {
            return !(origin_.x() + len_ < other.origin_.x() ||
                     origin_.x() > other.origin_.x() + other.len_ ||
                     origin_.y() + len_ < other.origin_.y() ||
                     origin_.y() > other.origin_.y() + other.len_);
        }


        /**
         * @brief Casts this square to another numeric type.
         * @tparam U The target type for the cast.
         * @return A new Square with the origin and length cast to the target type.
         */
        template <typename U>
        Square<U> cast() const {
            return Square<U>(origin_.template cast<U>(), static_cast<U>(len_));
        }


        /**
         * @brief Gets the size of the square as a Size object.
         * @return A Size object with height and width both equal to the square's length.
         */
        flat::Size<T> size() const {
            return flat::Size<T>(len_, len_);
        }
    };
}