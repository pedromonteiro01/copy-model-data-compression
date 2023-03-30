# Algorithmic Information Theory - 1st Project

 Lab work nº1 --- Due: 29 Mar 2023 <br>

 > **1** **Copy models for data compression**

 Data compression is obtained through the exploration of self
 similarities. There are several ways of attaining this goal, some of
 them will be studied in this course. In this work, it is intended to
 address one of them, which relies on the idea that some data sources
 can be viewed as being produced by replicating parts already produced
 in the past, although with some possible modifications. Generically,
 we refer to this process as a **copy model**.

 A copy model predicts that the next outcome will be a symbol that has
 occured in the past. This is done by maintaining a pointer referring
 to the symbol being copied, as well as some additional information,
 needed to estimate how reliable are those predictions.

 Let us denote by *xn* 1= *x*1*x*2 *. . . xn, xi ∈* Σ*,* the sequence
 of outputs (symbols from the source alphabet Σ) that the information
 source has generated until instant *n*. For example, if Σ = *{*0*,*
 1*}*, then we may have *x*8 1= 01001101. In this example, we have *x*1
 = 0, *x*2 = 1, *x*3 = 0, and so on. Then, for example if the copy
 pointer *p* = 4, then *xn−p* = *x*8*−*4 = *x*4 = 0.

 In practical terms, we need to estimate the probability of the next
 symbol, *xn*, being the same as the currently predicted symbol,
 *xn−p*, where *p \>* 0 is the pointer handled by the copy model.

 > **1.1** **The estimation of probabilities**

 The idea is to collect counts that represent the number of times that
 each symbol has been correctly predicted (*Nh*, denoting the number of
 hits), versus the number of times that it was wrongly predicted (*Nf*,
 denoting the number of prediction fails), and use these counters for
 estimating a probability. This can be done directly using the relative
 frequency, i.e., saying that the probability of the next prediction
 being a hit is *Nh/*(*Nh* + *Nf*). However, this suffers from the
 problem of assigning zero probability to events that
 were not seen during the construction of the model. That would be the
 case, for example, for the first time the probability is calculated.
 This problem can be overcome using a"smoothing" parameter for
 estimating the probabilities, i.e.,

 *P*(hit) *≈*                       (*Nh* + *α*) / (*Nh* + *Nf* + 2*α*)             

 where *α* is the smoothing parameter (the value "2" equals the number
 of events that are being predicted, in this example two, hit or fail).
 Note that, using this estimator, the first probability that is
 estimated is equal to 1*/*2, because, when the copy model is started,
 both *Nh* and *Nf* are zero. Also, note that this is just an example.
 In practice, at each coding step (i.e., for each symbol being
 encoded), we need a distribution of probabilities for all the symbols
 of the alphabet, i.e., *P*(*s*)*, ∀s ∈* Σ.

 Having the model computed, we can estimate the amount of information
 that a new symbol, *s*, needs to be represented. This is given by *−*
 log2 *P*(*s*).1

 >  **2**  **Work to be done**

 1\. Develop a program, named cpm, that implements a copy model. Note that the
 pointer associated to the copy model needs to be repositioned from
 time to time. This happens when the performance of the model drops
 below a certain threshold (i.e., the relation between the number of
 hits and the number of fails becomes too low). This repositioning
 needs to be done according to the previous *k* symbols that have been
 encoded, i.e., we need to look for a past occurrence of the string
 *xn−k*+1 *. . . xn*.

 All required parameters to control the model should be passed as
 command line arguments. This program should provide the estimated
 total number of bits for encoding a certain file, as well as the
 average number of bits per symbol.

 2\. Using cpm as a starting point, develop a program for automatic
 text generation (named cpm gen) that, based on an example text, is
 able to generate text that follows that model.

 3\. Elaborate a report, where you describe all the steps and decisions
 taken during the development of the work. Include relevant and
 illustrative results that were obtained. In particular, a discussion
 regarding the effects of the variation of the pa-rameters on the
 compression performance and computation time required. Besides the
 texts that you choose, it is mandatory to include entropy measures for
 the text chry.txt, available in moodle.

> **3** **How to deliver the work**

 The work should be developed and made available to the teachers using
 a repository fol-lowing the structure suggested in Fig. 1 (if needed,
 further instructions will be provided during the classes). The
 developed software should be compatible with the Linux operat-ing
 system. It should include a README file, explaining, with sufficient
 detail, how to build the program and all the parameters that it
 accepts. It should also include, at least, how to run a concrete
 example.

## How to run it

Compile
```
g++ -std=c++11 cpm.cpp -o cpm
```

Just run the executable file
```
./cpm <filename> <k> <alpha> <fail_threshold>
```