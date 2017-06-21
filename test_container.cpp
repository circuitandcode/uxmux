#include "test_container.h"

#include <iostream>

/* TODO: All this */

test_container::test_container(struct fb_fix_screeninfo* finfo, struct fb_var_screeninfo* vinfo){
	std::cout << "ctor test_container" << std::endl;
    m_finfo = finfo;
    m_vinfo = vinfo;
    m_back_buffer = static_cast<uint32_t*>(mmap(0, vinfo->yres_virtual * finfo->line_length, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, off_t(0)));
}

test_container::~test_container(void){
	std::cout << "dtor ~test_container" << std::endl;
}

inline uint32_t test_container::pixel_color(uint8_t r, uint8_t g, uint8_t b, struct fb_var_screeninfo *vinfo) {
    return static_cast<uint32_t>(r<<vinfo->red.offset | g<<vinfo->green.offset | b<<vinfo->blue.offset);
}

void test_container::swap_buffer(litehtml::uint_ptr hdc) {
    int i;
    for (i=0; i<(m_vinfo->yres_virtual * m_finfo->line_length)/4; i++) {
        ((uint32_t*)(hdc))[i] = m_back_buffer[i];
    }
}

void test_container::draw_rect(litehtml::uint_ptr hdc, const litehtml::position& rect, litehtml::web_color color) {
    // draw_rect(hdc, rect.x, rect.y, rect.width, rect.height, color);
    draw_rect(hdc, rect.x, rect.y, rect.width, rect.height, litehtml::web_color(0xff, 0, 0xff));
}

void test_container::draw_rect(litehtml::uint_ptr hdc, int xpos, int ypos, int width, int height, litehtml::web_color color) {
    std::cout << "   draw_rect, at (" << xpos << ", " << ypos << "), size (" << width << ", " << height << "), color (" << static_cast<int>(color.red) << ", " << static_cast<int>(color.green) << ", " << static_cast<int>(color.blue) << ")" << std::endl;

    long x, y;
    for (x = xpos; x < width; x++) {
        for (y = ypos; y < height; y++) {
            long location = (x+m_vinfo->xoffset)*(m_vinfo->bits_per_pixel/8) + (y+m_vinfo->yoffset)*m_finfo->line_length;
            *(reinterpret_cast<uint32_t*>(hdc+location)) = pixel_color(color.red, color.green, color.blue, m_vinfo);
        }
    }
}

litehtml::uint_ptr test_container::create_font(const litehtml::tchar_t* faceName, int size, int weight, litehtml::font_style italic, unsigned int decoration, litehtml::font_metrics* fm){
	std::cout << "create_font: " << faceName << std::endl;
	return 0;
}

void test_container::delete_font(litehtml::uint_ptr hFont){
	std::cout << "delete_font" << std::endl;
}

int test_container::text_width(const litehtml::tchar_t* text, litehtml::uint_ptr hFont){
	std::cout << "text_width" << std::endl;
	return strlen(text)*get_default_font_size();
}

void test_container::draw_text(litehtml::uint_ptr hdc, const litehtml::tchar_t* text, litehtml::uint_ptr hFont, litehtml::web_color color, const litehtml::position& pos){
	std::cout << "draw_text: " << text << ", at (" << pos.x << ", " << pos.y << "), size (" << pos.width << ", " << pos.height << ")" << std::endl;
    if (strcmp(text, " ")==0)
        draw_rect(hdc, pos.x, pos.y, pos.width, get_default_font_size(), color);
    else
        draw_rect(hdc, pos.x, pos.y, pos.width, get_default_font_size(), litehtml::web_color(0xff, 0x0, 0xff));
}

int test_container::pt_to_px(int pt){
	std::cout << "pt_to_px: " << pt << std::endl;
	return pt;
}

int test_container::get_default_font_size() const{
	std::cout << "get_default_font_size" << std::endl;
	return 16;
}

const litehtml::tchar_t* test_container::get_default_font_name() const{
	std::cout << "get_default_font_name" << std::endl;
    return "Times New Roman";
}

void test_container::draw_list_marker(litehtml::uint_ptr hdc, const litehtml::list_marker& marker){
	std::cout << "draw_list_marker" << std::endl;
}

void test_container::load_image(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, bool redraw_on_ready){
	std::cout << "load_image" << std::endl;
}

void test_container::get_image_size(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, litehtml::size& sz){
	std::cout << "get_image_size" << std::endl;
}

void test_container::draw_background(litehtml::uint_ptr hdc, const litehtml::background_paint& bg){
	std::cout << "draw_background" << std::endl;
}

void test_container::draw_borders(litehtml::uint_ptr hdc, const litehtml::borders& borders, const litehtml::position& draw_pos, bool root){
	std::cout << "draw_borders" << std::endl;
    draw_rect(hdc, draw_pos.x, draw_pos.y, draw_pos.width, borders.top.width, borders.top.color);
    draw_rect(hdc, draw_pos.x, draw_pos.y+draw_pos.height, draw_pos.width, borders.bottom.width, borders.bottom.color);
    draw_rect(hdc, draw_pos.x, draw_pos.y, borders.left.width, draw_pos.height, borders.left.color);
    draw_rect(hdc, draw_pos.x+draw_pos.width, draw_pos.y, borders.right.width, draw_pos.height, borders.right.color);
}

void test_container::set_caption(const litehtml::tchar_t* caption){
	std::cout << "set_caption" << std::endl;
}

void test_container::set_base_url(const litehtml::tchar_t* base_url){
	std::cout << "set_base_url" << std::endl;
}

void test_container::link(const std::shared_ptr<litehtml::document>& doc, const litehtml::element::ptr& el){
	std::cout << "link" << std::endl;
}

void test_container::on_anchor_click(const litehtml::tchar_t* url, const litehtml::element::ptr& el){
	std::cout << "on_anchor_click" << std::endl;
}

void test_container::set_cursor(const litehtml::tchar_t* cursor){
	std::cout << "set_cursor" << std::endl;
}

void test_container::transform_text(litehtml::tstring& text, litehtml::text_transform tt){
	std::cout << "transform_text" << std::endl;
}

void test_container::import_css(litehtml::tstring& text, const litehtml::tstring& url, litehtml::tstring& baseurl){
	std::cout << "import_css" << std::endl;
}

void test_container::set_clip(const litehtml::position& pos, const litehtml::border_radiuses& bdr_radius, bool valid_x, bool valid_y){
	std::cout << "set_clip" << std::endl;
}

void test_container::del_clip(){
	std::cout << "del_clip" << std::endl;
}

void test_container::get_client_rect(litehtml::position& client) const{
	std::cout << "get_client_rect (" << m_vinfo->xres << ", " << m_vinfo->yres << ")" << std::endl;
    client.x = 0;
    client.y = 0;
    client.width = m_vinfo->xres;
    client.height = m_vinfo->yres;
}

std::shared_ptr<litehtml::element> test_container::create_element(const litehtml::tchar_t* tag_name, const litehtml::string_map& attributes, const std::shared_ptr<litehtml::document>& doc){
	std::cout << "create_element: " << tag_name << std::endl;
	return 0;
}

void test_container::get_media_features(litehtml::media_features& media) const{
	std::cout << "get_media_features" << std::endl;
    litehtml::position client;
    get_client_rect(client);
    media.type = litehtml::media_type_screen;
    media.width = client.width;
    media.height = client.height;
    media.device_width = m_vinfo->xres;
    media.device_height = m_vinfo->yres;
    media.color = 8;
    media.monochrome = 0;
    media.color_index = 256;
    media.resolution = 96;
}

void test_container::get_language(litehtml::tstring& language, litehtml::tstring& culture) const{
	std::cout << "get_language" << std::endl;
    language = _t("en");
    culture = _t("");
}
