#ifndef POINT_H
#define POINT_H


class Point
{
    public:
        Point();
        Point(int p);
        double get(int j);
        void add(double& data, int j);

        ~Point();

        void show(int p);

    private:
        double* y;
};

#endif // POINT_H
