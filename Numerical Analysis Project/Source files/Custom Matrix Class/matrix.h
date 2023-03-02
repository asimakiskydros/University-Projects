#ifndef EX_3_MATRIX_H
#define EX_3_MATRIX_H

#include <vector>

class matrix{
private:
    int length;
    int width;
    std::vector<double> *data;

public:
    matrix(int length, int width){
        this->length = length;
        this->width = width;
        this->data = new std::vector<double>[this->length];
        for(int i = 0; i < this->length; i++)
            for (int j = 0; j < this->width; j++)
                this->data[i].push_back(0);
    }
    ~matrix(){
        delete [] this->data;
    }
    virtual double get(int index_i, int index_j) const{
        return this->data[index_i][index_j];
    }
    virtual bool set(int index_i, int index_j, double value){
        if(index_i >= 0 && index_i < this->length && index_j >= 0 && index_j < this->width){
            this->data[index_i][index_j] = value;
            return true;
        }
        return false;
    }
    int get_length() const{
        return this->length;
    }
    int get_width() const{
        return this->width;
    }
    virtual matrix *copy() const{
        auto* copy = new matrix(this->length,this->width);
        for(int i = 0; i < this->length; i++)
            for(int j = 0; j < this->width ; j++)
                copy->set(i, j ,this->data[i][j]);
        return copy;
    }
    bool swap_rows(int row_1, int row_2){
        if(row_1 >= 0 && row_1 < this->length && row_2 >= 0 && row_2 < this->length){
            this->data[row_1].swap(this->data[row_2]);
            return true;
        }
        return false;
    }
    /*matrix& multiply(const double &factor){
        for(int i = 0; i < this->length; i++)
            for(int j = 0; j < this->width; j++)
                this->data[i][j] *= factor;
        return *this;
    }*/
    double infinity_norm() const{
        double hold_max[this->length];
        //initialize every row of hold_max to the absolute sum of A's corresponding row
        //(if the input matrix is a single column this process simply sets every hold_max's slot to the absolute value
        //of A's corresponding slot)
        for(int i=0;i<this->length;i++){
            double sum = 0;
            for(int j=0;j<this->width;j++)
                sum += std::abs(this->get(i, j));
            hold_max[i] = sum;
        }
        //find max
        double max = hold_max[0];
        for(int i = 1; i < this->length; i++)
            if(hold_max[i] > max)
                max = hold_max[i];

        return max;
    }
    void print(std::ostream& o) const{
        for(int i = 0 ; i < this->length ; i++) {
            for (double &j: this->data[i])
                o<< j << "   ";
            o<<std::endl;
        }
    }
};
matrix* multiply(const matrix &one, const matrix &two){
    int temp_length = one.get_length();
    int temp_width = two.get_width();
    int common_width = one.get_width();
    //multiplication demands width-length equality
    if(common_width != two.get_length())
        return nullptr;

    auto* product = new matrix(temp_length,temp_width);
    for(int i = 0; i < temp_length; i++)
        for(int j =0; j < temp_width; j++){
            double sum = 0;
            for(int k = 0; k< common_width; k++)
                sum += one.get(i, k)*two.get(k, j);
            product->set(i, j, sum);
        }
    return product;
}

#endif //EX_3_MATRIX_H
