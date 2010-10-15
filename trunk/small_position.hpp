#ifndef SMALL_POSITION_HPP
#define SMALL_POSITION_HPP

#include "common.hpp"

struct SmallPosition
{
		// Unsigned char used to hold both x and y value. 
		unsigned char xy;
		SmallPosition() {xy = 0;}
        
		/*
		Constructor, takes a char x and a char y. Calls set(char x,char y).
		*/
        SmallPosition(char x, char y)
        {
                set(x,y);
        }

		/*
		Copy Constructor between SmallPosition and Position. Goes kaput if
		values higher than 15 are added. (15 is okay. 2^4 is limit). 
		*/
		SmallPosition(const Position & pos){
			this->xy = (pos.x << 4) | pos.y;
		} 

		/*
		Bitshifts x value to the 4 high bits. Y value remains the same. 
		Kaput if higher values than 15 are added (15 is okay. 2^4 is limit). 
		*/
        void set(char x, char y)
        {
                this->xy = (x << 4) | y;
        }

		/*
		Easiest getter I could make. returns y as a char. 
		*/
		char y(){
			return (xy & 0xF);
		}
		/* 
		Const version
		*/
		char y() const{
			return (xy & 0xF);
		}
		/*
		Easiest getter I could make. returns x as a char. 
		*/
		char x(){	
			return (xy >> 4);
		}
		/* 
		Const version
		*/
		char x() const{	
			return (xy >> 4);
		}

		/*
			Lazy way to do it, but...
			runs set(x,0);
		*/
		void setX(char x){
			set(x,0);
		}
		
		/*
			Lazy way to do it, but...
			runs set(0,y);
		*/
		void setY(char y){
			set(0,y);
		}

		// ==
		// Can Compare between Position and SmallPosition if values are <16.
		bool operator==(const SmallPosition & other) const
        {
                return (this->x() == other.x()) && (this->y() == other.y());
        }
		bool operator==(const Position & other) const
        {
                return (this->x() == other.x) && (this->y() == other.y);
        }

		// !=
		// Can Compare between Position and SmallPosition if values are <16.
        bool operator!=(const SmallPosition & other) const
        {
                return !(*this == other);
        }
		  bool operator!=(const Position & other) const
        {
                return !(*this == other);
        }


        SmallPosition operator+(const SmallPosition & other) const
        {
                return SmallPosition(other.x()+this->x(), other.y()+this->y());
        }
        SmallPosition up()
        {
			return SmallPosition(x(), y()-1);
        }
        SmallPosition right()
        {
                return SmallPosition(x()+1, y());
        }
        SmallPosition down()
        {
                return SmallPosition(x(), y()+1);
        }
        SmallPosition left()
        {
                return SmallPosition(x()-1, y());
        }
        
		/*
		Adds the SmallPosition together with the provided parameter one.
		*/
        void addPosition(SmallPosition pos) {
				char x = this->x() + pos.x();	// add together x values.
				char y = this->y() + pos.y();	// add together y values.
                set(x,y);						// Set bits. 
        }

        SmallPosition getDirection(int dir){
                switch(dir){
                case LEFT:
                        return left();
                        break;
                case RIGHT:
                        return right();
                        break;
                case UP:
                        return up();
                        break;
                case DOWN:
                        return down();
                        break;
                default:
                        return SmallPosition(0,0);
                }
        }
};

#endif