#!/usr/bin/ruby

begin
(15..22).each do | sum_i_j |
  d = sum_i_j/2
  [d - 2, d - 1, d, d + 1, d + 2].each do | i |
    j = sum_i_j - i
    r = 2**i
    c = 2**j
    [100, 10000].each do | range |
      puts "t: 1,2,3 sum_i_j: #{sum_i_j} i: #{i} range: #{range}"
      `./washington 1 #{r} #{c} #{range} "./new_gen/t1r#{r}c#{c}range#{range}.gr"`
      `./washington 2 #{r} #{c} #{range} "./new_gen/t2r#{r}c#{c}range#{range}.gr"`
      `./washington 3 #{r} #{c} #{range} "./new_gen/t3r#{r}c#{c}range#{range}.gr"`
    end
  end
end

(17..24).each do | sum_i_j |
  ni_ = [sum_i_j/2, sum_i_j - sum_i_j/2].max
  (0..4).each do | plus |
    ni = ni_ + plus
    n = 2**ni
    d = 2**(sum_i_j - ni)
    [100, 10000].each do | range |
      puts "t: 4 sum_i_j: #{sum_i_j} i: #{ni} j: #{sum_i_j - ni} range: #{range}"
      `./washington 4 #{n} #{d} #{range} "./new_gen/t4n#{n}d#{d}range#{range}.gr"`
    end
  end
end

(17..24).each do | exp |
  di_ = if exp.even? then 4 else 3 end
  di  = (exp - di_)/2
  d_ = 2**di_
  d  = 2**di
  [100, 10000].each do | range |
    puts "t: 5 exp: #{exp} di: #{di} Di: #{di_} range: #{range}"
    `./washington 5 #{d} #{d_} #{range} "./new_gen/t5d#{d}D#{d_}range#{range}.gr"`
  end
end

(17..24).each do | exp |
  di_ = if exp.even? then 4 else 3 end
  d_ = 2**di_
  b  = (exp - di_)/2
  [b - 2, b - 1, b, b + 1, b + 2].each do | i |
    n = 2**i
    m = 2**(exp - di_ - i)
    [100, 10000].each do | range |
      puts "t: 6,7,8 exp: #{exp} Di: #{di_} i: #{i} j: #{exp - di_ - i} range: #{range}"
      `./washington 6 #{n} #{m} #{d_} #{range} "./new_gen/t6n#{n}m#{m}D#{d_}range#{range}.gr"`
      `./washington 7 #{n} #{m} #{d_} #{range} "./new_gen/t7n#{n}m#{m}D#{d_}range#{range}.gr"`
      `./washington 8 #{n} #{m} #{d_} #{range} "./new_gen/t8n#{n}m#{m}D#{d_}range#{range}.gr"`
    end
  end
end

(16..23).each do | exp |
  n = 2**exp
  puts "t: 9 exp: #{exp} n: #{n}"
  `./washington 9 #{n} "./new_gen/t9n#{n}.gr"`
end

# this range is different from the others (that have always eight values)
# because takes more than 30m to generate an instance with n = 2^19
(14..18).each do | exp |
  n = 2**exp
  puts "t: 10 exp: #{exp} n: #{n}"
  `./washington 10 #{n} "./new_gen/t10n#{n}.gr"`
end
end

#very_big = 1_000_000
#(15..22).each do | exp |
#  [4, 10].each do | ni |
#    n = 2**ni
#    b = exp/2 
#    [b - 2, b - 1, b, b + 1, b + 2].each do | i |
#      c = 2**i
#      m = 2**(exp - i)
#      puts "t: 11 ni: #{ni} exp: #{exp} i: #{i} j: #{exp - i} very_big: #{very_big}"
#      `./washington 11 #{n} #{m} #{c} #{very_big} "./new_gen/t11n#{n}m#{m}c#{c}vb#{very_big}.gr"`
#    end
#  end
#end

