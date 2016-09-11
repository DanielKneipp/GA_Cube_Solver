#pragma once

#include <stdexcept>

typedef unsigned long ulong;
typedef unsigned short ushort;
typedef unsigned int uint;

template< typename _T >
struct Array2D
{
    _T ** m;
    ulong rows, cols;

    Array2D() 
        : m( 0 )
        , rows( 0 )
        , cols( 0 )
    {}

    Array2D( ulong rows, ulong cols ) { this->create( rows, cols ); }

    Array2D( const Array2D< _T > & other ) // Clones the other object
    {
        this->create( other.rows, other.cols );
        other.copyTo( *this );
    }

    Array2D( Array2D< _T >&& other )
    {
        this->rows = other.rows;
        this->cols = other.cols;
        this->m = other.m;

        other.m = 0;
    }

    Array2D< _T >& operator=( const Array2D< _T >& other )
    {
        if( this->m )
            this->clear();

        this->create( other.rows, other.cols );
        other.copyTo( *this );

        return *this;
    }

    Array2D< _T >& operator=( Array2D< _T >&& other )
    {
        if( this->m )
            this->clear();

        this->rows = other.rows;
        this->cols = other.cols;
        this->m = other.m;

        other.m = 0;

        return *this;
    }

    ~Array2D()
    {
        this->clear();
    }

    void create( ulong rows, ulong cols )
    {
        this->m = new _T * [ rows ];
        for( ulong i = 0; i < rows; ++i )
            this->m[ i ] = new _T[ cols ];

        this->rows = rows; this->cols = cols;
    }

    void clear()
    {
        if( this->m )
        {
            for( ulong i = 0; i < this->rows; ++i )
            {
                if( this->m[ i ] )
                {
                    delete[] this->m[ i ];
                }
            }
            delete[] this->m;
            this->m = 0;
        }

        this->rows = 0; this->cols = 0;
    }

    void copyTo( Array2D & other ) const
    {
        if( other.cols != this->cols || other.rows != this->rows )
            throw std::runtime_error( "Array2D::copyTo -> 2D arrays are not of the same size" );

        for( ulong i = 0; i < this->rows; ++i )
            for( ulong j = 0; j < this->cols; ++j )
                other.m[ i ][ j ] = this->m[ i ][ j ];
    }

    void rot90()
    {
        if( this->rows == this->cols )
        {
            ulong N = this->rows;
            for( ulong i = 0; i < N / 2; ++i )
            {
                for( ulong j = i; j < N - i - 1; ++j )
                {
                    _T temp = this->m[ i ][ j ];

                    this->m[ i ][ j ] = this->m[ N - 1 - j ][ i ];
                    this->m[ N - 1 - j ][ i ] = this->m[ N - 1 - i ][ N - 1 - j ];
                    this->m[ N - 1 - i ][ N - 1 - j ] = this->m[ j ][ N - 1 - i ];
                    this->m[ j ][ N - 1 - i ] = temp;
                }
            }
        }
        else
        {
            ulong new_m_cols = this->rows;
            ulong new_m_rows = this->cols;
            _T ** new_m = new _T *[ new_m_rows ];
            for( ulong i = 0; i < new_m_rows; ++i )
                new_m[ i ] = new _T[ new_m_rows ];

            for( ulong i = 0; i < this->rows; ++i )
                for( ulong j = 0; j < this->cols; ++j )
                    new_m[ j ][ new_m_cols - i - 1 ] = this->m[ i ][ j ];

            this->clear();
            this->m = new_m; this->rows = new_m_rows; this->cols = new_m_cols;
        }
    }

    void rot90i()
    {
        if( this->rows == this->cols )
        {
            ulong N = this->rows;
            for( ulong i = 0; i < N / 2; ++i )
            {
                for( ulong j = i; j < N - i - 1; ++j )
                {
                    _T temp = this->m[ i ][ j ];
                    this->m[ i ][ j ] = this->m[ j ][ N - 1 - i ];
                    this->m[ j ][ N - 1 - i ] = this->m[ N - 1 - i ][ N - 1 - j ];
                    this->m[ N - 1 - i ][ N - 1 - j ] = this->m[ N - 1 - j ][ i ];
                    this->m[ N - 1 - j ][ i ] = temp;
                }
            }
        }
        else
        {
            ulong new_m_cols = this->rows;
            ulong new_m_rows = this->cols;
            _T ** new_m = new _T *[ new_m_rows ];
            for( ulong i = 0; i < new_m_rows; ++i )
                new_m[ i ] = new _T[ new_m_rows ];

            for( ulong i = 0; i < this->rows; ++i )
                for( ulong j = 0; j < this->cols; ++j )
                    new_m[ new_m_rows - j - 1 ][ i ] = this->m[ i ][ j ];

            this->clear();
            this->m = new_m; this->rows = new_m_rows; this->cols = new_m_cols;
        }
    }

    void rot180()
    {
        for( ulong i = 0; i < this->rows / 2; ++i )
        {
            for( ulong j = 0; j < this->cols; ++j )
            {
                _T aux = this->m[ i ][ j ];
                this->m[ i ][ j ] = this->m[ this->rows - i - 1 ][ this->cols - j - 1 ];
                this->m[ this->rows - i - 1 ][ this->cols - j - 1 ] = aux;
            }
        }

        if( this->rows % 2 != 0 )
        {
            ulong i = this->rows / 2;
            for( ulong j = 0; j < this->cols / 2; ++j )
            {
                _T aux = this->m[ i ][ j ];
                this->m[ i ][ j ] = this->m[ this->rows - i - 1 ][ this->cols - j - 1 ];
                this->m[ this->rows - i - 1 ][ this->cols - j - 1 ] = aux;
            }
        }
    }
};