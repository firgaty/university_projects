#ifndef INCLUDE_SQUARE_HPP_
#define INCLUDE_SQUARE_HPP_

#include <algorithm>
#include <vector>

#include "Model/Colored.hpp"
#include "Model/GameObject/GameObject.hpp"

class Square : public Colored
{
protected:
    std::vector<const GameObject *> _objects;
    bool _accessible;
    static const std::size_t _size = 16;

public:
    Square();
    explicit Square(Color color);
    explicit Square(bool accessible);
    Square(bool accessible, Color color);
    Square(bool accessible, Color color, const GameObject *object);
    virtual ~Square() {}

    const std::vector<const GameObject *> objects() const;
    const bool is_accessible() const;
    void add_object(const GameObject *o);
    const GameObject *remove_object(const std::size_t &index);
    const GameObject *remove_object(const GameObject *o);
    const GameObject *
    remove_object(const std::vector<const GameObject *>::iterator &it);
    const GameObject *get(size_t) const;
    const GameObject *get_last() const;
    const GameObject *remove_last();
    void empty();
    bool has_object(const GameObject *o);
    std::size_t index_of(const GameObject *o);
    std::vector<const GameObject *>::iterator it_of(const GameObject *o);

    bool is_empty() const;
    const size_t size() const;
};

#endif // INCLUDE_SQUARE_HPP_
