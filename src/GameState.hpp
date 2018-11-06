#ifndef GAMESTATE_H_DEFINED
#define GAMESTATE_H_DEFINED

class GameState {
public:
    virtual ~GameState() {};

    //  Tải trạng thái
    virtual void load() = 0;

    // huỷ bỏ trạng thái hiện tại và khởi tạo cho trạng thái mới
    virtual void unload() = 0;

    // update trạng thái hiện tại
    virtual void update() = 0;

    // vẽ trạng thái hiện tại ra màn hình
    virtual void draw() = 0;
};

#endif //GAMESTATE_H_DEFINED
