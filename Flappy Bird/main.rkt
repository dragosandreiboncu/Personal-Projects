#lang racket/gui

(require 2htdp/image)
(require 2htdp/universe)
(require lang/posn)

(require "random.rkt")
(require "constants.rkt")
(require racket/trace)
(provide next-state)
(provide next-state-bird)
(provide next-state-bird-onspace)
(provide change)

(provide get-pipes)
(provide get-pipe-x)
(provide next-state-pipes)
(provide add-more-pipes)
(provide clean-pipes)
(provide move-pipes)

(provide invalid-state?)
(provide check-ground-collision)
(provide check-pipe-collisions)

(provide draw-frame)

(provide get-initial-state)
(provide get-bird)
(provide get-bird-y)
(provide get-bird-v-y)

(provide get-pipes)
(provide get-pipe-x)

(provide get-score)

(provide get-abilities)
(provide get-abilities-visible)
(provide get-abilities-active)
(provide get-variables)
(provide get-variables-gravity)
(provide get-variables-momentum)
(provide get-variables-scroll-speed)


(define-struct ptitza ( x y v-y) #:transparent)
(define-struct pipe (x y) #:transparent)
(define-struct variables (gravity momentum scroll-speed) #:transparent)
(define-struct stare ( ptitza pipes score) #:transparent)

(define (get-initial-state)
  (stare (ptitza bird-x bird-initial-y 0) (list (pipe scene-width  (+ added-number (random random-threshold)))) 0))
              
(define (get-bird state)
  (stare-ptitza state))

(define (get-bird-y bird)
 (let* ((y (ptitza-y bird)))
       y))

(define (get-bird-x bird)
  (ptitza-x bird))

(define (next-state-bird bird gravity)
    (struct-copy ptitza bird
                 [y (+ (get-bird-y bird) (get-bird-v-y bird))]
                 [v-y (+ (get-bird-v-y bird ) gravity)]
                 ))

(define (get-bird-v-y bird)
  (ptitza-v-y bird))

(define (next-state-bird-onspace bird momentum)
  (struct-copy ptitza bird
                 [v-y (- 0 momentum)]
                 ))

(define (change current-state pressed-key)
    (if (not (key=? pressed-key " "))
        current-state
       (struct-copy stare current-state
                   [ptitza (next-state-bird-onspace (get-bird current-state) initial-momentum )])))


(define (get-pipes state)
  (stare-pipes state))

(define(get-pipe-x pipe)
  (pipe-x pipe))
(define(get-pipe-y pipe)
  (pipe-y pipe))

(define (move-pipes pipes scroll-speed)
  (map (lambda (el) (pipe (- (get-pipe-x el) scroll-speed) (get-pipe-y el)))  pipes))

(define (clean-pipes pipes)
  (if (<= (+ (get-pipe-x (car pipes)) pipe-width) 0)
      (cdr pipes)
      pipes))

(define (add-more-pipes pipes)
  (if ( < (length pipes) no-pipes)
      (append pipes (list (pipe (+ (get-pipe-x (car (reverse pipes))) pipe-width pipe-gap)
                    (+ added-number (random random-threshold))) ))
      pipes))

(define (next-state-pipes pipes scroll-speed)
  (add-more-pipes (clean-pipes (move-pipes pipes scroll-speed))))

(define (get-score state)
  (stare-score state))

(define (check-ground-collision bird)
  (if (not(>= (+ (get-bird-y bird) bird-height) ground-y))
      #f
      #t))

(define (invalid-state? state)
  (if ( not (or (check-ground-collision (get-bird state))
          (check-pipe-collisions (get-bird state) (get-pipes state))))
       #f
        #t))

(define (check-pipe-collisions bird pipes)
  (let parkour ((truba pipes))
    (if (null? truba)
        #f
        (if (or (check-collision-rectangles
                                              (make-posn (get-bird-x bird) (get-bird-y bird))
                                              (make-posn (+ (get-bird-x bird) bird-width) (+ (get-bird-y bird) bird-height))
                                              (make-posn (get-pipe-x (car truba)) 0)
                                              (make-posn (+ (get-pipe-x (car truba)) pipe-width) (get-pipe-y (car truba))))
                 
                       (check-collision-rectangles
                                              (make-posn (get-bird-x bird) (get-bird-y bird))
                                              (make-posn (+ (get-bird-x bird) bird-width) (+ (get-bird-y bird) bird-height))
                                              (make-posn (get-pipe-x (car truba)) ( + (get-pipe-y (car truba)) pipe-self-gap))
                                              (make-posn (+ (get-pipe-x (car truba)) pipe-width) ( - scene-height ground-height))))
                 
            #t
            (parkour (cdr truba))))))

(define (check-collision-rectangles A1 A2 B1 B2)
  (match-let ([(posn AX1 AY1) A1]
              [(posn AX2 AY2) A2]
              [(posn BX1 BY1) B1]
              [(posn BX2 BY2) B2])
    (and (< AX1 BX2) (> AX2 BX1) (< AY1 BY2) (> AY2 BY1))))

(define (next-state state)
  (stare (next-state-bird (get-bird state) initial-gravity)
         (next-state-pipes (get-pipes state) initial-scroll-speed)
         (+ (get-score state) 0.1))
  )

(define bird-image (rectangle bird-width bird-height  "solid" "yellow"))
(define ground-image (rectangle scene-width ground-height "solid" "brown"))
(define initial-scene (rectangle scene-width scene-height "solid" "white"))

(define initial-pipe (rectangle pipe-width  scene-height "solid" "green"))
(define pipe-gap-im (rectangle (+ pipe-width 2) pipe-self-gap "solid" "white"))
  
(define text-family (list "Gill Sans" 'swiss 'normal 'bold #f))
(define (score-to-image x)
(if SHOW_SCORE
	(apply text/font (~v (round x)) 24 "indigo" text-family)
	empty-image))

(define (draw-frame state)
  (place-image bird-image (+ (get-bird-x (get-bird state))(quotient bird-width 2)) (+ (get-bird-y (get-bird state)) (quotient bird-height 2))
               (place-image ground-image (quotient scene-width 2)  (+ ground-y (quotient ground-height 2))
                            (place-image (score-to-image (get-score state)) text-x text-y
                                         (place-pipes (get-pipes state) initial-scene)))))

(define (place-pipes pipes scene)
  (let iter ((acc scene) (trubs pipes))
    (if (null? trubs)
        acc
        ( iter (place-image pipe-gap-im (+ (get-pipe-x (car trubs)) (quotient pipe-width 2)) (+ (get-pipe-y (car trubs))(quotient pipe-self-gap 2))
                                  (place-image initial-pipe (+ (get-pipe-x (car trubs)) (quotient pipe-width 2)) (quotient scene-height 2) acc)) (cdr trubs))))
  )
        

(module+ main
	(big-bang (get-initial-state)
	 [on-tick next-state (/ 1.0 fps)]
	 [to-draw draw-frame]
	 [on-key change]
	 [stop-when invalid-state?]
	 [close-on-stop #t]
	 [record? #f]))
