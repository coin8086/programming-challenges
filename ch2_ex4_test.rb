#!/usr/bin/env ruby

require_relative 'test_helper'
require 'set'

sentences = [
  %w(bob and kate like the cat very much),
  %w(nothing is difficult to a willing heart),
  %w(if i had known you i would have helped you),
  %w(there is too much work to finish it on time without your help),
  %w(do not break a young girl s heart),
  %w(long long before i fell in love with a pretty young girl),
  %w(how time flies you just do not give me any chance kate),
  %w(let us do something meaningful or i will go back home for bed),
  %w(your letter for me might be in care of kate),
  %w(kate is in bad with lucy for some unknown reason),
  %w(he would not keep in touch with us wherever he was),
  %w(here is a five pound note you can keep the change),
  %w(progress is slow but we keep battling on),
  %w(it is easy to open a shop but hard to keep it),
  %w(once you make a promise you should keep it tony),
  %w(she keeps the family on two hundred dollars a week),
  %w(i will only keep you a few minutes),
  %w(we are all keeping well we are all keeping well we are all keeping well),
  %w(she kept her past secret from him),
  %w(she kept a diary for over twenty years),
  %w(she wears a hat to keep the sun out of her eyes),
  %w(they looked forward very much to seeing him again),
  %w(if you are looking to buy a new car i suggest you borrow some money from him),
  %w(the country must have a long hard look at the tragedy of unemployment),
  %w(i took one look at the coat and decided i would have to buy it),
  %w(he sat down at the table with a weary look on his face),
  %w(my mother wore a troubled look when she heard of my father s illness),
  %w(we threw a look of contempt at him because he told a deliberate lie),
  %w(i knew something was wrong everyone was giving me funny looks),
  %w(she used her good looks to compensate her lack of intelligence),
  %w(she had a very disappointed look when she heard the news),
  %w(she assumed a look of innocence),
  %w(i have had a good look but i can not find it anywhere),
  %w(he often looks before and after when he deals with problems),
  %w(when you look deeper you will find some differences between them),
  %w(why do not you come to stay with us next time you visit durham),
  %w(what we must be able to do is to stay impartial at all times),
  %w(we have taken on extra staff to cope with the increased workload manager),
  %w(we can not have that sort of thing happening so what),
  %w(it is sad that we have to part company with them),
  %w(her eyes are the most catching i have ever seen mum),
  %w(i am afraid you have not appreciated the urgency of the matter),
  %w(i suppose you also have a caste system in your society do not you),
  %w(i have been puzzling about this question for weeks now),
  %w(still it is an ill wind you will have an unexpected holiday),
  %w(many heroic men and women have died in defense of liberty),
  %w(in point of cost we will have to discuss it at the next meeting),
  %w(please verify each item you have pricked down),
  %w(keep away from that house they have scarlet fever papa),
  %w(recent reports in the press have been hotly denied),
  %w(how odd they have gone through the eccentric yet foolish thing),
  %w(it must be difficult to play various personae in the same movie),
  %w(the law provides that these ancient buildings must be preserved mary),
  %w(a close friendship gradually grew up between them),
  %w(excuse me do you mind if we close the window right now),
  %w(the shop is just on the ropes and must surely have to close soon mum),
  %w(it is a fact of life and you must face it mary),
  %w(the populace at large are opposed to sudden change),
  %w(the sudden noise set the dog barking),
  %w(her sudden departure has disarranged my plans),
  %w(the boy got a good beating for breaking the third window),
  %w(clean clothes and good manners are prepossessing),
  %w(the method seems good but it needs to be tried out),
  %w(if we can pull through this recession we will be in good shape),
  %w(he glimpsed at my new watch and said it was a good bargain),
  %w(he is such a good swimmer that he makes me look sick),
  %w(do not you be so fucking formal with me david),
  %w(stop fucking around and come and give me a hand cowboy),
  %w(you are fucking well coming whether you want to or not),
  %w(renaming multiple files at a shell prompt is always considered as a black art),
  %w(he was able to inject both color and humor into his rather formidable subject),
  %w(some asp net functions generate client script and inject it into the page),
  %w(i have solved the problem but i am not all together satisfied with my solution),
  %w(ilikeit),
]

bad_sentences = [
  %w(ilikeii),
  %w(xyy yzz eez xee hhe zza),
  %w(bob and kate like the caa),
  %w(bob and kayy like the cat),
  %w(bbb and kate like the cat),
  %w(if you are looking to buy a new car i suggest you borrow some money from hxm),
  %w(if you are looking to buy a new car i suggest you borrow some money xrom him),
  %w(if you are looking to buy a new car i suggest you borrow some xoney from him),
  %w(if you are looking to buy a new car i suggest you borrow xome money from him),
  %w(if you are looking to buy a new car i suggest you xorrow some money from him),
  %w(if you are looking to buy a new car i suggest xou borrow some money from him),
  %w(if you are looking to buy a new car i xuggest you borrow some money from him),
  %w(if you are looking to buy a new car x suggest you borrow some money from him),
  %w(if you are looking to buy a new cax i suggest you borrow some money from him),
  %w(if you are looking to buy a xew car i suggest you borrow some money from him),
  %w(if you are looking to buy x new car i suggest you borrow some money from him),
  %w(if you are looking to xuy a new car i suggest you borrow some money from him),
  %w(if you are looking tx buy a new car i suggest you borrow some money from him),
  %w(if you are loxking to buy a new car i suggest you borrow some money from him),
  %w(if you xre looking to buy a new car i suggest you borrow some money from him),
  %w(if xou are looking to buy a new car i suggest you borrow some money from him),
  %w(xf you are looking to buy a new car i suggest you borrow some money from him),
]


def encrypt(s, alphabet)
  base = 'a'.ord
  enc_s = []
  s.each do |w|
    enc_w = []
    w.each_char do |l|
      enc_w << alphabet[l.ord - base]
    end
    enc_s << enc_w.join
  end
  enc_s
end

def asterisk(s)
  enc_s = []
  s.each do |w|
    enc_s << '*' * w.size
  end
  enc_s
end

test(File.expand_path(__FILE__)) do |input, output|
  dict = Set.new
  alphabet = ('a'..'z').to_a
  enc = []

  sentences.each do |s|
    s.each do |w|
      dict << w
    end

    alphabet.shuffle!
    enc << encrypt(s, alphabet)
  end

  input = File.open(input, 'wb')
  output = File.open(output, 'wb')

  input.puts dict.size
  dict.sort.each do |w|
    input.puts w
  end

  enc.each_with_index do |e, i|
    input.puts(e.join ' ')
    output.puts(sentences[i].join ' ')
  end

  bad_sentences.each do |s|
    alphabet.shuffle!
    input.puts(encrypt(s, alphabet).join ' ')
    output.puts(asterisk(s).join ' ')
  end
  input.close
  output.close
end
