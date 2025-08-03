module;
#include <stdexcept>
#include <type_traits>

export module mite.size;

export namespace mite {

    template <typename T>
    struct Size {
    static_assert(std::is_arithmetic_v<T>, "Size must be arithmetic type");

    protected:
        T height_;
        T width_;

    public:
        explicit Size(T height = 0, T width = 0) : height_(height), width_(width) {}

        Size operator+(const Size& other) const {
            return Size(height_ + other.height_, width_ + other.width_);
        }

        Size operator-(const Size& other) const {
            return Size(height_ - other.height_, width_ - other.width_);
        }

        Size& operator+=(const Size& other) {
            height_ += other.height_;
            width_ += other.width_;
            return *this;
        }

        Size& operator-=(const Size& other) {
            height_ -= other.height_;
            width_ -= other.width_;
            return *this;
        }

        Size operator*(T scalar) const {
            return Size(height_ * scalar, width_ * scalar);
        }

        Size& operator*=(T scalar) {
            height_ *= scalar;
            width_ *= scalar;
            return *this;
        }

        Size operator/(T scalar) const {
            if (scalar == 0) {
                throw std::invalid_argument("Division by zero is not allowed.");
            }
            if constexpr (std::is_integral_v<T>) {
                if (height_ % scalar != 0 || width_ % scalar != 0) {
                    throw std::invalid_argument("Division results in non-integer values.");
                }
            }
            return Size(height_ / scalar, width_ / scalar);
        }

        Size& operator/=(T scalar) {
            if (scalar == 0) {
                throw std::invalid_argument("Division by zero is not allowed.");
            }
            if constexpr (std::is_integral_v<T>) {
                if (height_ % scalar != 0 || width_ % scalar != 0) {
                    throw std::invalid_argument("Division results in non-integer values.");
                }
            }
            height_ /= scalar;
            width_ /= scalar;
            return *this;
        }

        bool operator==(const Size& other) const {
            return height_ == other.height_ && width_ == other.width_;
        }

        bool operator!=(const Size& other) const {
            return !(*this == other);
        }

        T height() const {
            return height_;
        }

        T width() const {
            return width_;
        }

        Size& of_height(T new_height) {
            height_ = new_height;
            return *this;
        }

        Size& of_width(T new_width) {
            width_ = new_width;
            return *this;
        }

        bool can_fit(const Size& other) const {
            return height_ >= other.height_ && width_ >= other.width_;
        }

        // Compare area of two points
        bool operator<(const Size& other) const {
            return (height_ * width_) < (other.height_ * other.width_);
        }
        bool operator>(const Size& other) const {
            return (height_ * width_) > (other.height_ * other.width_);
        }
        bool operator<=(const Size& other) const {
            return (height_ * width_) <= (other.height_ * other.width_);
        }
        bool operator>=(const Size& other) const {
            return (height_ * width_) >= (other.height_ * other.width_);
        }
    };

    namespace size {

        template<typename T>
        concept HasHeightMember = requires(T t) {
            t.height;
        };

        template<typename T>
        concept HasHeightMethod = requires(T t) {
            t.height();
        };

        template<typename T>
        concept HasHeight = HasHeightMember<T> || HasHeightMethod<T>;

        template<typename T>
        concept HasWidthMember = requires(T t) {
            t.width;
        };

        template<typename T>
        concept HasWidthMethod = requires(T t) {
            t.width();
        };

        template<typename T>
        concept HasWidth = HasWidthMember<T> || HasWidthMethod<T>;

    } // namespace size

    template<typename T>
        concept IsSize = size::HasHeight<T> && size::HasWidth<T>;
}
