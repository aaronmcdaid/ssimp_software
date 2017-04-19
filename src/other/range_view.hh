#include"range.hh"
#include<functional>

namespace view {
    struct {} ref_wraps;
    struct {} unzip_and_apply_and_collect;

    template<typename R, typename tag>
    struct temporary_tagged_holder {
        R m_r;
        temporary_tagged_holder(R r) : m_r(std::move(r)) {}
    };

    template<typename R>
    auto operator| (R r, decltype(ref_wraps) );

    template<typename R>
    struct ref_wraps_impl {
        R m_range_with_front_ref;

        bool            empty()         const   { return   range:: empty    (m_range_with_front_ref)  ; }
        auto            front_val()     const   { return std:: ref( range:: front_ref(m_range_with_front_ref) ); }
        void            advance()               { range:: advance(m_range_with_front_ref); }
    };

    template<typename R>
    auto operator| (R r, decltype(ref_wraps) ) {
        return ref_wraps_impl<R> {move(r)};
    }

    template<typename R>
    auto operator| (R r, decltype(unzip_and_apply_and_collect) ) {
        return temporary_tagged_holder<R, decltype(unzip_and_apply_and_collect)> { std::move(r) };
    }

    template<typename R, typename F
        , class ...
        , typename applied_value_type =
            decltype( utils:: apply   ( std::declval<F>()
                                      , range:: pull(std::declval<R>())
            ))
        , bool is_it_void = std:: is_same<void, applied_value_type>{}
        , typename = std:: enable_if_t<is_it_void>
        >
    void operator| (temporary_tagged_holder<R, decltype(unzip_and_apply_and_collect)> r_holder, F && f)
    {
        while(!r_holder.m_r.empty()) {
            utils:: apply   ( std::forward<F>(f)
                            , range:: pull(r_holder.m_r)
            );
        }
    }
} // namespace view
