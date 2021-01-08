#ifndef INCREMENT_H
#define INCREMENT_H

#include <algorithm>

// increment_up

template<class PopulationIter, class SampleIter,
		 class Distance, class UniformRandomBitGenerator>
	SampleIter increment_up(PopulationIter first, PopulationIter last,
							SampleIter out, Distance n,
							UniformRandomBitGenerator && g) ;


// Below: code from the algorithm header

// sample
template<class PopulationIter, class SampleIter,
		 class Distance, class UniformRandomBitGenerator>
  SampleIter sample(PopulationIter first, PopulationIter last,
						SampleIter out, Distance n,
						UniformRandomBitGenerator&& g);

namespace ranges {
  template<input_iterator I, sentinel_for<I> S,
		   weakly_incrementable O, class Gen>
	requires (forward_iterator<I> || random_access_iterator<O>) &&
			 indirectly_copyable<I, O> &&
			 uniform_random_bit_generator<remove_reference_t<Gen>>
	O sample(I first, S last, O out, iter_difference_t<I> n, Gen&& g);
	
  template<input_range R, weakly_incrementable O, class Gen>
	requires (forward_range<R> || random_access_iterator<O>) &&
			 indirectly_copyable<iterator_t<R>, O> &&
			 uniform_random_bit_generator<remove_reference_t<Gen>>
	O sample(R&& r, O out, range_difference_t<R> n, Gen&& g);
}

// replace
  template<class ForwardIter, class T>
    constexpr void replace(ForwardIter first, ForwardIter last,
                           const T& old_value, const T& new_value);
  template<class ExecutionPolicy, class ForwardIter, class T>
    void replace(ExecutionPolicy&& exec,
                 ForwardIter first, ForwardIter last,
                 const T& old_value, const T& new_value);
  template<class ForwardIter, class Pred, class T>
    constexpr void replace_if(ForwardIter first, ForwardIter last,
                              Pred pred, const T& new_value);
  template<class ExecutionPolicy, class ForwardIter, class Pred, class T>
    void replace_if(ExecutionPolicy&& exec,
                    ForwardIter first, ForwardIter last,
                    Pred pred, const T& new_value);

  namespace ranges {
    template<input_iterator I, sentinel_for<I> S, class T1, class T2, class Proj = identity>
      requires indirectly_writable<I, const T2&> &&
               indirect_binary_predicate<ranges::equal_to, projected<I, Proj>, const T1*>
      constexpr I
        replace(I first, S last, const T1& old_value, const T2& new_value, Proj proj = {});
    template<input_range R, class T1, class T2, class Proj = identity>
      requires indirectly_writable<iterator_t<R>, const T2&> &&
               indirect_binary_predicate<ranges::equal_to,
                                         projected<iterator_t<R>, Proj>, const T1*>
      constexpr borrowed_iterator_t<R>
        replace(R&& r, const T1& old_value, const T2& new_value, Proj proj = {});
    template<input_iterator I, sentinel_for<I> S, class T, class Proj = identity,
             indirect_unary_predicate<projected<I, Proj>> Pred>
      requires indirectly_writable<I, const T&>
      constexpr I replace_if(I first, S last, Pred pred, const T& new_value, Proj proj = {});
    template<input_range R, class T, class Proj = identity,
             indirect_unary_predicate<projected<iterator_t<R>, Proj>> Pred>
      requires indirectly_writable<iterator_t<R>, const T&>
      constexpr borrowed_iterator_t<R>
        replace_if(R&& r, Pred pred, const T& new_value, Proj proj = {});
  }

  template<class InputIter, class OutputIter, class T>
    constexpr OutputIter replace_copy(InputIter first, InputIter last,
                                          OutputIter result,
                                          const T& old_value, const T& new_value);
  template<class ExecutionPolicy, class ForwardIter1, class ForwardIter2, class T>
    ForwardIter2 replace_copy(ExecutionPolicy&& exec,
                                  ForwardIter1 first, ForwardIter1 last,
                                  ForwardIter2 result,
                                  const T& old_value, const T& new_value);
  template<class InputIter, class OutputIter, class Pred, class T>
    constexpr OutputIter replace_copy_if(InputIter first, InputIter last,
                                             OutputIter result,
                                             Pred pred, const T& new_value);
  template<class ExecutionPolicy, class ForwardIter1, class ForwardIter2,
           class Pred, class T>
    ForwardIter2 replace_copy_if(ExecutionPolicy&& exec,
                                     ForwardIter1 first, ForwardIter1 last,
                                     ForwardIter2 result,
                                     Pred pred, const T& new_value);

  namespace ranges {
    template<class I, class O>
      using replace_copy_result = in_out_result<I, O>;

    template<input_iterator I, sentinel_for<I> S, class T1, class T2,
             output_iterator<const T2&> O, class Proj = identity>
      requires indirectly_copyable<I, O> &&
               indirect_binary_predicate<ranges::equal_to, projected<I, Proj>, const T1*>
      constexpr replace_copy_result<I, O>
        replace_copy(I first, S last, O result, const T1& old_value, const T2& new_value,
                     Proj proj = {});
    template<input_range R, class T1, class T2, output_iterator<const T2&> O,
             class Proj = identity>
      requires indirectly_copyable<iterator_t<R>, O> &&
               indirect_binary_predicate<ranges::equal_to,
                                         projected<iterator_t<R>, Proj>, const T1*>
      constexpr replace_copy_result<borrowed_iterator_t<R>, O>
        replace_copy(R&& r, O result, const T1& old_value, const T2& new_value,
                     Proj proj = {});

    template<class I, class O>
      using replace_copy_if_result = in_out_result<I, O>;

    template<input_iterator I, sentinel_for<I> S, class T, output_iterator<const T&> O,
             class Proj = identity, indirect_unary_predicate<projected<I, Proj>> Pred>
      requires indirectly_copyable<I, O>
      constexpr replace_copy_if_result<I, O>
        replace_copy_if(I first, S last, O result, Pred pred, const T& new_value,
                        Proj proj = {});
    template<input_range R, class T, output_iterator<const T&> O, class Proj = identity,
             indirect_unary_predicate<projected<iterator_t<R>, Proj>> Pred>
      requires indirectly_copyable<iterator_t<R>, O>
      constexpr replace_copy_if_result<borrowed_iterator_t<R>, O>
        replace_copy_if(R&& r, O result, Pred pred, const T& new_value,
                        Proj proj = {});
  }

#endif // INCREMENT_H
