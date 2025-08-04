module;
#include <type_traits>

export module mite.rect;

import mite.size;
import mite.point;

export namespace mite {

    /**
     * @brief A template class representing a 2D rectangle with geometric operations.
     * @tparam T The type of the coordinates and dimensions, must be an arithmetic type.
     */
    template <typename T>
    struct Rect {
        static_assert(std::is_arithmetic_v<T>, "Rect must be of an arithmetic type");

    protected:
        flat::Point<T> origin_; ///< The origin point (bottom-left corner) of the rectangle.
        flat::Size<T> size_; ///< The size (width and height) of the rectangle.

    public:

        /**
         * @brief Constructs a Rect with given origin point and size.
         * @param origin The origin point of the rectangle (default is Point at 0,0).
         * @param size The size of the rectangle (default is Size with 0,0).
         */
        explicit Rect(flat::Point<T> origin = flat::Point<T>(), flat::Size<T> size = flat::Size<T>())
            : origin_(origin), size_(size) {}

        /**
         * @brief Constructs a Rect with given origin point, width and height.
         * @param origin The origin point of the rectangle.
         * @param width The width of the rectangle.
         * @param height The height of the rectangle.
         */
        explicit Rect(flat::Point<T> origin, T width, T height)
            : origin_(origin), size_(flat::Size<T>(height, width)) {}

        /**
         * @brief Constructs a Rect with given coordinates and size.
         * @param x The x-coordinate of the origin.
         * @param y The y-coordinate of the origin.
         * @param size The size of the rectangle.
         */
        explicit Rect(T x, T y, flat::Size<T> size)
            : origin_(flat::Point<T>(x, y)), size_(size) {}

        /**
         * @brief Constructs a Rect with given coordinates, width and height.
         * @param x The x-coordinate of the origin.
         * @param y The y-coordinate of the origin.
         * @param width The width of the rectangle.
         * @param height The height of the rectangle.
         */
        explicit Rect(T x, T y, T width, T height)
            : origin_(flat::Point<T>(x, y)), size_(flat::Size<T>(height, width)) {}

        /**
         * @brief Gets the origin point of the rectangle.
         * @return The origin point of the rectangle.
         */
        flat::Point<T> origin() const {
            return origin_;
        }

        /**
         * @brief Gets the size of the rectangle.
         * @return The size of the rectangle.
         */
        flat::Size<T> size() const {
            return size_;
        }

        /**
         * @brief Gets the width of the rectangle.
         * @return The width of the rectangle.
         */
        T width() const {
            return size_.width();
        }

        /**
         * @brief Gets the height of the rectangle.
         * @return The height of the rectangle.
         */
        T height() const {
            return size_.height();
        }

        /**
         * @brief Sets the origin point of the rectangle.
         * @param new_origin The new origin point.
         */
        void set_origin(const flat::Point<T>& new_origin) {
            origin_ = new_origin;
        }

        /**
         * @brief Sets the size of the rectangle.
         * @param new_size The new size.
         */
        void set_size(const flat::Size<T>& new_size) {
            size_ = new_size;
        }

        /**
         * @brief Sets the width of the rectangle.
         * @param new_width The new width.
         */
        void set_width(T new_width) {
            size_.of_width(new_width);
        }

        /**
         * @brief Sets the height of the rectangle.
         * @param new_height The new height.
         */
        void set_height(T new_height) {
            size_.of_height(new_height);
        }

        /**
         * @brief Gets the x-coordinate of the rectangle's origin.
         * @return The x-coordinate of the origin point.
         */
        T x() const {
            return origin_.x();
        }

        /**
         * @brief Gets the y-coordinate of the rectangle's origin.
         * @return The y-coordinate of the origin point.
         */
        T y() const {
            return origin_.y();
        }

        /**
         * @brief Sets the x-coordinate of the rectangle's origin.
         * @param new_x The new x-coordinate.
         * @return A reference to this rectangle for method chaining.
         */
        Rect& at_x(T new_x) {
            origin_.at_x(new_x);
            return *this;
        }

        /**
         * @brief Sets the y-coordinate of the rectangle's origin.
         * @param new_y The new y-coordinate.
         * @return A reference to this rectangle for method chaining.
         */
        Rect& at_y(T new_y) {
            origin_.at_y(new_y);
            return *this;
        }

        /**
         * @brief Sets the origin point of the rectangle.
         * @param new_origin The new origin point.
         * @return A reference to this rectangle for method chaining.
         */
        Rect& at(const flat::Point<T>& new_origin) {
            origin_ = new_origin;
            return *this;
        }

        /**
         * @brief Sets the size of the rectangle.
         * @param new_size The new size.
         * @return A reference to this rectangle for method chaining.
         */
        Rect& of_size(const flat::Size<T>& new_size) {
            size_ = new_size;
            return *this;
        }

        /**
         * @brief Sets the width of the rectangle.
         * @param new_width The new width.
         * @return A reference to this rectangle for method chaining.
         */
        Rect& of_width(T new_width) {
            size_.of_width(new_width);
            return *this;
        }

        /**
         * @brief Sets the height of the rectangle.
         * @param new_height The new height.
         * @return A reference to this rectangle for method chaining.
         */
        Rect& of_height(T new_height) {
            size_.of_height(new_height);
            return *this;
        }

        /**
         * @brief Checks if two rectangles are equal.
         * @param other The other rectangle to compare.
         * @return True if the rectangles have the same origin and size, false otherwise.
         */
        bool operator==(const Rect& other) const {
            return origin_ == other.origin_ && size_ == other.size_;
        }

        /**
         * @brief Checks if two rectangles are not equal.
         * @param other The other rectangle to compare.
         * @return True if the rectangles are not equal, false otherwise.
         */
        bool operator!=(const Rect& other) const {
            return !(*this == other);
        }

        /**
         * @brief Calculates the area of the rectangle.
         * @return The area of the rectangle (width * height).
         */
        T area() const {
            return size_.width() * size_.height();
        }

        /**
         * @brief Calculates the perimeter of the rectangle.
         * @return The perimeter of the rectangle (2 * (width + height)).
         */
        T perimeter() const {
            return static_cast<T>(2) * (size_.width() + size_.height());
        }

        /**
         * @brief Checks if this rectangle can fit another rectangle within its bounds.
         * @param other The other rectangle to check.
         * @return True if the other rectangle can fit entirely within this rectangle, false otherwise.
         */
        bool can_fit(const Rect& other) const {
            return other.origin_.x() >= origin_.x() &&
                   other.origin_.y() >= origin_.y() &&
                   (other.origin_.x() + other.size_.width()) <= (origin_.x() + size_.width()) &&
                   (other.origin_.y() + other.size_.height()) <= (origin_.y() + size_.height());
        }

        /**
         * @brief Checks if this rectangle can fit a size within its bounds.
         * @param size The size to check.
         * @return True if the size can fit within this rectangle, false otherwise.
         */
        bool can_fit(const flat::Size<T>& size) const {
            return size_.can_fit(size);
        }

        /**
         * @brief Checks if a point is contained within the rectangle.
         * @param point The point to check.
         * @return True if the point is within the rectangle's bounds (inclusive), false otherwise.
         */
        bool contains(const flat::Point<T>& point) const {
            return point.x() >= origin_.x() && point.x() <= (origin_.x() + size_.width()) &&
                   point.y() >= origin_.y() && point.y() <= (origin_.y() + size_.height());
        }

        /**
         * @brief Checks if this rectangle intersects with another rectangle.
         * @param other The other rectangle to check for intersection.
         * @return True if the rectangles intersect, false otherwise.
         */
        bool intersects(const Rect& other) const {
            return !(origin_.x() + size_.width() < other.origin_.x() ||
                     origin_.x() > other.origin_.x() + other.size_.width() ||
                     origin_.y() + size_.height() < other.origin_.y() ||
                     origin_.y() > other.origin_.y() + other.size_.height());
        }

        /**
         * @brief Gets the top-left corner of the rectangle.
         * @return The top-left corner point.
         */
        flat::Point<T> top_left() const {
            return flat::Point<T>(origin_.x(), origin_.y() + size_.height());
        }

        /**
         * @brief Gets the top-right corner of the rectangle.
         * @return The top-right corner point.
         */
        flat::Point<T> top_right() const {
            return flat::Point<T>(origin_.x() + size_.width(), origin_.y() + size_.height());
        }

        /**
         * @brief Gets the bottom-left corner of the rectangle (same as origin).
         * @return The bottom-left corner point.
         */
        flat::Point<T> bottom_left() const {
            return origin_;
        }

        /**
         * @brief Gets the bottom-right corner of the rectangle.
         * @return The bottom-right corner point.
         */
        flat::Point<T> bottom_right() const {
            return flat::Point<T>(origin_.x() + size_.width(), origin_.y());
        }

        /**
         * @brief Gets the center point of the rectangle.
         * @return The center point of the rectangle.
         */
        flat::Point<T> center() const {
            return flat::Point<T>(
                origin_.x() + size_.width() / static_cast<T>(2),
                origin_.y() + size_.height() / static_cast<T>(2)
            );
        }

        /**
         * @brief Casts this rectangle to another numeric type.
         * @tparam U The target type for the cast.
         * @return A new Rect with the origin and size cast to the target type.
         */
        template <typename U>
        Rect<U> cast() const {
            return Rect<U>(
                origin_.template cast<U>(),
                flat::Size<U>(static_cast<U>(size_.height()), static_cast<U>(size_.width()))
            );
        }

        /**
         * @brief Checks if this rectangle is a square.
         * @return True if width equals height, false otherwise.
         */
        bool is_square() const {
            return size_.width() == size_.height();
        }

        /**
         * @brief Scales the rectangle by a factor.
         * @param factor The scaling factor.
         * @return A new Rect that is scaled by the given factor.
         */
        Rect scale(T factor) const {
            return Rect(origin_, size_ * factor);
        }

        /**
         * @brief Translates the rectangle by a given offset.
         * @param offset The offset to translate by.
         * @return A new Rect that is translated by the given offset.
         */
        Rect translate(const flat::Point<T>& offset) const {
            return Rect(origin_ + offset, size_);
        }

        /**
         * @brief Expands the rectangle by a given amount in all directions.
         * @param amount The amount to expand by.
         * @return A new Rect that is expanded by the given amount.
         */
        Rect expand(T amount) const {
            return Rect(
                flat::Point<T>(origin_.x() - amount, origin_.y() - amount),
                flat::Size<T>(size_.height() + static_cast<T>(2) * amount,
                              size_.width() + static_cast<T>(2) * amount)
            );
        }

        /**
         * @brief Contracts the rectangle by a given amount in all directions.
         * @param amount The amount to contract by.
         * @return A new Rect that is contracted by the given amount.
         */
        Rect contract(T amount) const {
            return expand(-amount);
        }
    };
}
