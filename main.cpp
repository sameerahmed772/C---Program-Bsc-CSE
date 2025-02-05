#include <iostream>
#include <vector>
using namespace std;

class Booking {
private:
    string productName;
    int id;
    string check_in, check_out;
    float price, total_cost, discount_price;
    int guests, discount;
    float rewards;
    bool isPaid;

public:
    Booking() : productName("N/A"), id(0), check_in("N/A"), check_out("N/A"), price(0),
                guests(0), discount(0), rewards(0), discount_price(0), isPaid(false) {}

    Booking(string p, int i, string chkin, string chkout, float pr, int g, int d)
        : productName(p), id(i), check_in(chkin), check_out(chkout), price(pr),
          guests(g), discount(d), isPaid(false) {
        calculateDiscount();
        calculateRewards();
    }

    /*~Booking() {
        cout << "Booking No: " << id << " is destroyed." << endl;
    }*/

    void calculateDiscount() {
        discount_price = price - (price * discount / 100);
    }

    void calculateRewards() {
        rewards = discount_price * 0.05;
    }

    void markAsPaid() {
        isPaid = true;
        cout << "Booking ID " << id << " is now marked as PAID.\n";
    }

    void showInfo() const {
        cout << "\nBooking Details: " << endl;
        cout << "Product Name: " << productName << endl;
        cout << "Booking ID: " << id << endl;
        cout << "Check-in: " << check_in << " | Check-out: " << check_out << endl;
        cout << "Number of Guests: " << guests << endl;
        cout << "Original Price: " << price << " Taka" << endl;
        cout << "Discounted Price: " << discount_price << " Taka" << endl;
        cout << "Rewards Earned: " << rewards << " Taka" << endl;
        cout << "Payment Status: " << (isPaid ? "PAID" : "NOT PAID") << endl;
    }

    int getID() const { return id; }
    bool getPaymentStatus() const { return isPaid; }
};

struct Product {
    int id;
    string name;
    float price;
    int discount;
};

vector<Product> products = {
    {1, "Standard Room", 5000, 10},
    {2, "Deluxe Room", 8000, 15},
    {3, "Suite", 12000, 20}
};

vector<Booking> bookings;
int bookingCounter = 1;

void makeBooking() {
    int productId, days;
    string checkin, checkout;
    cout << "Enter Product ID (1-3): "; cin >> productId;
    cout << "Enter Check-in Date: "; cin >> checkin;
    cout << "Enter Check-out Date: "; cin >> checkout;
    cout << "Enter Number of Days: "; cin >> days;

    if (productId < 1 || productId > products.size()) {
        cout << "Invalid Product ID!\n";
        return;
    }

    Product selectedProduct = products[productId - 1];
    float totalPrice = selectedProduct.price * days;
    Booking newBooking(selectedProduct.name, bookingCounter++, checkin, checkout, totalPrice, 1, selectedProduct.discount);
    bookings.push_back(newBooking);
    cout << "Booking Created Successfully!\n";
}

void viewBookings() {
    if (bookings.empty()) {
        cout << "No bookings found!\n";
        return;
    }
    for (const auto& booking : bookings) {
        booking.showInfo();
    }
}

void checkPaymentStatus() {
    int id;
    cout << "Enter Booking ID: "; cin >> id;
    for (auto& booking : bookings) {
        if (booking.getID() == id) {
            cout << "Payment Status: " << (booking.getPaymentStatus() ? "PAID" : "NOT PAID") << endl;
            return;
        }
    }
    cout << "Booking ID not found!\n";
}

void makePayment() {
    int id;
    cout << "Enter Booking ID to mark as paid: "; cin >> id;
    for (auto& booking : bookings) {
        if (booking.getID() == id) {
            booking.markAsPaid();
            return;
        }
    }
    cout << "Booking ID not found!\n";
}

void cancelBooking() {
    int id;
    cout << "Enter Booking ID to cancel: "; cin >> id;
    for (auto it = bookings.begin(); it != bookings.end(); ++it) {
        if (it->getID() == id) {
            bookings.erase(it);
            cout << "Booking ID " << id << " has been canceled.\n";
            return;
        }
    }
    cout << "Booking ID not found!\n";
}

int main() {
    int choice;
    do {
        cout << "\n----- Booking System Menu -----\n";
        cout << "1. Make a Booking\n";
        cout << "2. View Bookings\n";
        cout << "3. Check Payment Status\n";
        cout << "4. Make Payment\n";
        cout << "5. Cancel a Booking\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: makeBooking(); break;
            case 2: viewBookings(); break;
            case 3: checkPaymentStatus(); break;
            case 4: makePayment(); break;
            case 5: cancelBooking(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
