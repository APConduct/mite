module;
#include <stdexcept>
#include <type_traits>

export module mite.size;

export namespace mite {
    namespace flat {
        /**
        * @brief A template class representing a 2D size with arithmetic operations.
        * @tparam T The type of the dimensions, must be an arithmetic type.
        */
        template <typename T>
        struct Size {
            static_assert(std::is_arithmetic_v<T>, "Size must be arithmetic type");

        protected:
            T height_; ///< The height of the size.
            T width_; ///< The width of the size.

        public:
            /**
             * @brief Constructs a Size with given height and width.
             * @param height The height (default is 0).
             * @param width The width (default is 0).
             */
            explicit Size(T height = 0, T width = 0) : height_(height), width_(width) {
            }

            /**
             * @brief Adds two sizes.
             * @param other The other size to add.
             * @return A new Size that is the sum of this and the other size.
             */
            Size operator+(const Size& other) const {
                return Size(height_ + other.height_, width_ + other.width_);
            }

            /**
             * @brief Subtracts another size from this size.
             * @param other The other size to subtract.
             * @return A new Size that is the difference of this and the other size.
             */
            Size operator-(const Size& other) const {
                return Size(height_ - other.height_, width_ - other.width_);
            }

            /**
             * @brief Adds another size to this size.
             * @param other The other size to add.
             * @return A reference to this size after addition.
             */
            Size& operator+=(const Size& other) {
                height_ += other.height_;
                width_ += other.width_;
                return *this;
            }

            /**
             * @brief Subtracts another size from this size.
             * @param other The other size to subtract.
             * @return A reference to this size after subtraction.
             */
            Size& operator-=(const Size& other) {
                height_ -= other.height_;
                width_ -= other.width_;
                return *this;
            }

            /**
             * @brief Multiplies this size by a scalar.
             * @param scalar The scalar value to multiply by.
             * @return A new Size that is the result of the multiplication.
             */
            Size operator*(T scalar) const {
                return Size(height_ * scalar, width_ * scalar);
            }

            /**
             * @brief Multiplies this size by a scalar in-place.
             * @param scalar The scalar value to multiply by.
             * @return A reference to this size after multiplication.
             */
            Size& operator*=(T scalar) {
                height_ *= scalar;
                width_ *= scalar;
                return *this;
            }

            /**
             * @brief Divides this size by a scalar.
             * @param scalar The scalar value to divide by.
             * @return A new Size that is the result of the division.
             * @throws std::invalid_argument If scalar is zero or results in non-integer values for integral types.
             */
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

            /**
             * @brief Divides this size by a scalar in-place.
             * @param scalar The scalar value to divide by.
             * @return A reference to this size after division.
             * @throws std::invalid_argument If scalar is zero or results in non-integer values for integral types.
             */
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

            /**
             * @brief Checks if two sizes are equal.
             * @param other The other size to compare.
             * @return True if the sizes are equal, false otherwise.
             */
            bool operator==(const Size& other) const {
                return height_ == other.height_ && width_ == other.width_;
            }

            /**
             * @brief Checks if two sizes are not equal.
             * @param other The other size to compare.
             * @return True if the sizes are not equal, false otherwise.
             */
            bool operator!=(const Size& other) const {
                return !(*this == other);
            }

            /**
             * @brief Gets the height of the size.
             * @return The height.
             */
            T height() const {
                return height_;
            }

            /**
             * @brief Gets the width of the size.
             * @return The width.
             */
            T width() const {
                return width_;
            }

            /**
             * @brief Sets the height of the size.
             * @param new_height The new height.
             * @return A reference to this size.
             */
            Size& of_height(T new_height) {
                height_ = new_height;
                return *this;
            }

            /**
             * @brief Sets the width of the size.
             * @param new_width The new width.
             * @return A reference to this size.
             */
            Size& of_width(T new_width) {
                width_ = new_width;
                return *this;
            }

            /**
             * @brief Checks if this size can fit another size.
             * @param other The other size to check.
             * @return True if this size can fit the other size, false otherwise.
             */
            bool can_fit(const Size& other) const {
                return height_ >= other.height_ && width_ >= other.width_;
            }

            /**
             * @brief Compares the area of this size with another size.
             * @param other The other size to compare.
             * @return True if this size's area is less than the other size's area.
             */
            bool operator<(const Size& other) const {
                return (height_ * width_) < (other.height_ * other.width_);
            }

            /**
             * @brief Compares the area of this size with another size.
             * @param other The other size to compare.
             * @return True if this size's area is greater than the other size's area.
             */
            bool operator>(const Size& other) const {
                return (height_ * width_) > (other.height_ * other.width_);
            }

            /**
             * @brief Compares the area of this size with another size.
             * @param other The other size to compare.
             * @return True if this size's area is less than or equal to the other size's area.
             */
            bool operator<=(const Size& other) const {
                return (height_ * width_) <= (other.height_ * other.width_);
            }

            /**
             * @brief Compares the area of this size with another size.
             * @param other The other size to compare.
             * @return True if this size's area is greater than or equal to the other size's area.
             */
            bool operator>=(const Size& other) const {
                return (height_ * width_) >= (other.height_ * other.width_);
            }
        };
    }



    /**
         * @brief Concept to check if a type has a height member.
         */
    template <typename T>
    concept HasHeightMember = requires(T t)
    {
        t.height && std::is_arithmetic_v<decltype(t.height)>;
    };

    /**
     * @brief Concept to check if a type has a height() method.
     */
    template <typename T>
    concept HasHeightMethod = requires(T t)
    {
        t.height() && std::is_arithmetic_v<decltype(t.height())>;
    };

    /**
         * @brief Concept to check if a type has a width member.
         */
    template <typename T>
    concept HasWidthMember = requires(T t)
    {
        t.width && std::is_arithmetic_v<decltype(t.width)>;
    };

    /**
     * @brief Concept to check if a type has a width() method.
     */
    template <typename T>
    concept HasWidthMethod = requires(T t)
    {
        t.width() && std::is_arithmetic_v<decltype(t.width())>;
    };

    /**
         * @brief Concept to check if a type has a height (member or method).
         */
    template <typename T>
    concept HasHeight = HasHeightMember<T> || HasHeightMethod<T>;



    /**
     * @brief Concept to check if a type has a width (member or method).
     */
    template <typename T>
    concept HasWidth = HasWidthMember<T> || HasWidthMethod<T>;

    namespace flat {
        /**
         * @brief Concept to check if a type satisfies both height and width requirements.
         * @tparam T The type to check.
         * @details This concept ensures that the type has both height and width,
         * either as members or accessible through methods.
         */
        template <typename T>
        concept IsSize = HasHeight<T> && HasWidth<T>;

        /**
 * @brief Concept to check if a type has a `size` member.
 * @tparam T The type to check.
 * @details This concept ensures that the type has a member variable named `size`.
 */
        template <typename T>
        concept HasSizeMember = requires(T t)
        {
            t.size;
        };

        /**
         * @brief Concept to check if a type has a `size()` method.
         * @tparam T The type to check.
         * @details This concept ensures that the type has a method named `size()`.
         */
        template <typename T>
        concept HasSizeMethod = requires(T t)
        {
            t.size();
        };

        /**
         * @brief Concept to check if a type has a `size` (member or method).
         * @tparam T The type to check.
         * @details This concept ensures that the type has either a member variable named `size`
         * or a method named `size()`.
         */
        template <typename T>
        concept HasSize = HasSizeMember<T> || HasSizeMethod<T>;
    }

}



